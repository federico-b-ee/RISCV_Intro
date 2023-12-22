`include "Vr_RV32I_ISA.v"
`include "Vr_ALU.v"

module Vr_RV32I_Processor (
    input i_clk,
    input i_nrst,
    input [31:0] i_MEM_rdata,
    output [31:0] o_MEM_addr,
    output o_rEN,
    output [31:0] o_MEM_wdata,
    output [3:0] o_wMASK
);

    // Register Bank
    reg [31:0] PC = 0;
    reg [31:0] instr; 

    reg [31:0] REGISTERBANK [31:0];
    reg [31:0] register_rs1;
    reg [31:0] register_rs2;
    reg [31:0] register_rd;

    // RV32I ISA
    wire [9:0] instrtypes;
    wire [4:0] rs1, rs2, rd;
    wire [31:0] imm;
    wire [2:0] funct3;
    wire [6:0] funct7;

    parameter ALU_Rtype     = 0;
    parameter ALU_Itype     = 1;
    parameter Load_Itype    = 2;
    parameter Store_Stype   = 3;
    parameter Branch_Btype  = 4;
    parameter JAL_Jtype     = 5;
    parameter JALR_Itype    = 6;
    parameter LUI_Utype     = 7;
    parameter AUIPC_Utype   = 8;
    parameter System_Itype  = 9;

    Vr_RV32I_ISA RV32I_ISA (
        .i_instr(instr),
        .o_instrtypes(instrtypes),
        .o_rs1(rs1),
        .o_rs2(rs2),
        .o_rd(rd),
        .o_imm(imm), 
        .o_funct3(funct3),
        .o_funct7(funct7)
    );

    // ALU - The shifter can be optimized more too

   wire [31:0] PC_plus_imm = PC + imm;

    wire [31:0] PC_plus_4 = PC + 4;

    wire [31:0] ALU_in2 = (instrtypes[ALU_Rtype] | instrtypes[Branch_Btype])?register_rs2:imm;

    wire [31:0] ALUoutput;
    wire [31:0] wrDATA = (instrtypes[JAL_Jtype] || instrtypes[JALR_Itype])
                        ? PC_plus_4
                        : instrtypes[LUI_Utype]
                        ? imm
                        : instrtypes[AUIPC_Utype]
                        ? PC_plus_imm 
                        : instrtypes[Load_Itype]
                        ? ldDATA
                        : ALUoutput;

    wire wrEN = (state == EXEC && 
                !instrtypes[Load_Itype] && 
                !instrtypes[Store_Stype] && 
                !instrtypes[Branch_Btype]) || (state == WAIT_DATA);

    Vr_ALU ALU (
        .i_in1(register_rs1),
        .i_in2(ALU_in2),
        .i_instr(instr),
        .o_out(ALUoutput), 
        .o_ALUadd(ALUadd),
        .o_EQ(EQ),
        .o_LT(LT),
        .o_LTU(LTU)
    );

    //
    wire [31:0] ALUadd;
    wire EQ, LT, LTU;
    
    // Branch Handler -> The ALU can be used to decrease the LUTs needed.

    reg takeBranch;
    always @(*) begin
        case(funct3)
            3'b000: takeBranch = EQ;
            3'b001: takeBranch = !EQ;
            3'b100: takeBranch = LT;
            3'b101: takeBranch = !LT;
            3'b110: takeBranch = LTU;
            3'b111: takeBranch = !LTU;
            default: takeBranch = 1'b0;
        endcase
    end 
    
    wire [31:0] PCnext = ((instrtypes[Branch_Btype] && takeBranch) || instrtypes[JAL_Jtype])
                        ? PC_plus_imm
                        : (instrtypes[JALR_Itype]
                        ? {ALUadd[31:1], 1'b0}
                        : PC_plus_4);

    // Load and Store Handler

    // LOAD
    wire [31:0] loadstore_addr = register_rs1 + imm; // the implementation detects that the imm = imm_Itype or imm_Stype
    wire [15:0] LOAD_h = loadstore_addr[1] ? i_MEM_rdata[31:16] : i_MEM_rdata[15:0];
    wire [7:0]  LOAD_b = loadstore_addr[0] ? LOAD_h[15:8] : LOAD_h[7:0];

    wire EN_byte = (funct3[1:0] == 2'b00);
    wire EN_hw = (funct3[1:0] == 2'b01);

    wire LOAD_sign = !funct3[1] & (EN_byte ? LOAD_b[7] : LOAD_h[15]); //!funct3[1] -> not load word
    
    wire [31:0] ldDATA =    EN_byte ? {{24{LOAD_sign}}, LOAD_b} :
                            EN_hw ? {{16{LOAD_sign}}, LOAD_h} :
                            i_MEM_rdata;
    // STORE

    assign o_MEM_wdata[7:0] = register_rs2[7:0];

    assign o_MEM_wdata[15:8] = loadstore_addr[0] ? register_rs2[7:0] : register_rs2[15:8];

    assign o_MEM_wdata[23:16] = loadstore_addr[1] ? register_rs2[7:0] : register_rs2[23:16];

    assign o_MEM_wdata[31:24] = loadstore_addr[0] ? register_rs2[7:0] : 
                                loadstore_addr[1] ? register_rs2[15:8] : register_rs2[31:24];

                
    wire STORE_MASK =
        EN_byte     ?
            (loadstore_addr[1] ?
                (loadstore_addr[0] ? 4'b1000 : 4'b0100) :
                (loadstore_addr[0] ? 4'b0010 : 4'b0001)
                ) :
        EN_hw       ?
            (loadstore_addr[1] ? 4'b1100 : 4'b0011) :
            4'b1111;

    assign o_rEN = (state == FETCH_INSTR || state == LOAD);
    assign o_MEM_addr = (state == WAIT_INSTR || state == FETCH_INSTR) ? PC : loadstore_addr;
    assign o_wMASK = {4{(state == STORE)}} & STORE_MASK;

    // Datapath
    parameter FETCH_INSTR = 0, FETCH_REGS = 1, EXEC = 2, WAIT_INSTR = 3, LOAD = 4, WAIT_DATA = 5, STORE = 6;
    reg [2:0] state = FETCH_INSTR;

    always @(posedge i_clk) begin

        if(!i_nrst) begin
            PC    <= 0;
            state <= FETCH_INSTR;
            instr <= 32'b0000000_00000_00000_000_00000_0110011; // noop
        end else begin
            if (wrEN && rd != 5'b00000) begin
                REGISTERBANK[rd] <= wrDATA;
            end
        end

        case (state)
            FETCH_INSTR: begin
                state <= WAIT_INSTR;
            end
            WAIT_INSTR: begin
                instr <= i_MEM_rdata;
                state <= FETCH_REGS;
            end
            FETCH_REGS: begin
                register_rs1 <= REGISTERBANK[rs1];
                register_rs2 <= REGISTERBANK[rs2];
                state <= EXEC;
            end
            EXEC: begin
                if (!instrtypes[System_Itype]) begin 
                    PC <= PCnext;
                end
                state <= instrtypes[Load_Itype] ? LOAD : instrtypes[Store_Stype] ? STORE : FETCH_INSTR;
            end
            LOAD: begin
                state <= WAIT_DATA;
            end
            WAIT_DATA: begin
                state <= FETCH_INSTR;
            end
            STORE: begin
                state <= FETCH_INSTR;
            end
            default: begin
                state <= FETCH_INSTR;
            end
        endcase
        `ifdef TESTBENCH      
	        if(instrtypes[System_Itype]) $finish();
        `endif   
    end

    // Testbench

    `ifdef TESTBENCH   
        integer     i;
        initial begin
            for(i=0; i<32; ++i) begin
            REGISTERBANK[i] = 0;
            end
        end
        always @(posedge i_clk) begin
            if (state == EXEC) begin 
                $display("***************************************");
                $display("PC=%0d <= PC_next=%0d", PC, PCnext);
                $display("Immediate=%0d == %b", imm, imm);
                $display("Instr:%b", instr);
                $display("takeBranch:%b || funct3:%b", takeBranch, funct3);
                $display("ALU_in2:%0d == %b", ALU_in2, ALU_in2);
                $display("rs1:%0d == %b", register_rs1, register_rs1);
                case (1'b1)
                instrtypes[ALU_Rtype]:      $display(
                                                "PC=%0d // ALUreg rd=%d rs1=%d rs2=%d funct3=%b instr=%b",
                                                PC, rd, rs1, rs2, funct3, instr
                                            );
                instrtypes[ALU_Itype]:      $display(
                                                "PC=%0d // ALUimm rd=%d rs1=%d rs2=%d funct3=%b state=%d",
                                                PC, rd, rs1, rs2, funct3, state
                                            );
                instrtypes[Load_Itype]:     $display("PC=%0d // Load", PC);
                instrtypes[Store_Stype]:    $display("PC=%0d // Store", PC);
                instrtypes[Branch_Btype]:   $display("PC=%0d // PC_next=%0d // BRANCH // instr=%b", PC, PCnext, instr);
                instrtypes[JAL_Jtype]:      $display("PC=%0d // JAL", PC);
                instrtypes[JALR_Itype]:     $display("PC=%0d // JALR", PC);	
                instrtypes[LUI_Utype]:      $display("PC=%0d // LUI", PC);
                instrtypes[AUIPC_Utype]:    $display("PC=%0d // AUIPC", PC);
                instrtypes[System_Itype]:   $display("PC=%0d // SYSTEM", PC);
                endcase 
                $display("***************************************");
            end
        end
    `endif
endmodule