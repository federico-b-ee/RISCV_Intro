`include "Vr_CLockDivider.v"
`include "Vr_RV32I_ISA.v"
`include "Vr_ALU.v"


module SOC #(parameter N = 32, M = 5, LEDS = 8) (
    input  i_clk,        
    input  i_rst,      
    output [LEDS-1:0] o_leds, 
    input  RXD,        
    output TXD         
);

    reg [31:0] PC = 0;
    reg [31:0] instr; 

    // Register Bank
    reg [31:0] REGISTERBANK [31:0];
    reg [31:0] register_rs1;
    reg [31:0] register_rs2;
    reg [31:0] register_rd;
    
    // RAM
    `include "riscv_assembly.v"

    reg [31:0] MEM [255:0]; 
   

    integer L0_=4;
    initial begin
        ADD(x1,x0,x0);
        Label(L0_);
        ADDI(x1,x1,1);
        JAL(x0,LabelRef(L0_));
        EBREAK();
        endASM();
    end

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

    // ALU
    wire [31:0] ALUoutput;
    wire [31:0] wrDATA = (instrtypes[JAL_Jtype] || instrtypes[JALR_Itype])
                        ? (PC + 4)
                        : (instrtypes[LUI_Utype]
                        ? imm
                        : (instrtypes[AUIPC_Utype]
                            ? PC + imm
                            : ALUoutput));

    wire wrEN =   (state == EXEC && 
                    (instrtypes[ALU_Rtype] || 
                     instrtypes[ALU_Itype] || 
                     instrtypes[JAL_Jtype] ||
                     instrtypes[JAL_Jtype] ||
                     instrtypes[LUI_Utype] ||
                     instrtypes[AUIPC_Utype]));   

    Vr_ALU ALU (
        .i_in1(register_rs1),
        .i_in2(instrtypes[ALU_Rtype]?register_rs2:imm),
        .i_instr(instr),
        .o_out(ALUoutput)
    );
    
    // Branch Handler -> The ALU can be used to decrease the LUTs needed.

    reg takeBranch;
    always @(*) begin
        case(funct3)
        3'b000: takeBranch = (register_rs1 == register_rs2);
        3'b001: takeBranch = (register_rs1 != register_rs2);
        3'b100: takeBranch = ($signed(register_rs1) < $signed(register_rs2));
        3'b101: takeBranch = ($signed(register_rs1) >= $signed(register_rs2));
        3'b110: takeBranch = (register_rs1 < register_rs2);
        3'b111: takeBranch = (register_rs1 >= register_rs2);
        default: takeBranch = 1'b0;
        endcase
    end 
    
    wire [31:0] PCnext = ((instrtypes[Branch_Btype] && takeBranch) || instrtypes[JAL_Jtype])
                        ? PC + imm
                        : (instrtypes[JALR_Itype]
                        ? register_rs1 + imm
                        : PC + 4);

    // Datapath
    parameter FETCH = 0, REGS = 1, EXEC = 2;
    reg [1:0] state = FETCH;

    always @(posedge clk) begin

        if(i_rst) begin
            PC    <= 0;
            state <= FETCH;
            instr <= 32'b0000000_00000_00000_000_00000_0110011; // noop
        end else begin
            if (wrEN && rd != 5'b00000) begin
                REGISTERBANK[rd] <= wrDATA;
            end
        end

        case (state)
            FETCH: begin
                instr <= MEM[PC[31:2]];
                state <= REGS;
            end
            REGS: begin
                register_rs1 <= REGISTERBANK[rs1];
                register_rs2 <= REGISTERBANK[rs2];
                state <= EXEC;
            end
            EXEC: begin
                if (!instrtypes[System_Itype]) begin 
                    PC <= PCnext;
                end
                state <= FETCH;
            end
        endcase
        `ifdef TESTBENCH      
	        if(instrtypes[System_Itype]) $finish();
        `endif   
    end


    // ClockDivider
    wire clk, nrst, rst;

    Vr_ClockDivider #(.DIV(20)) CLK (
        .o_clk(clk),
        .i_clk(i_clk),
        .i_rst(rst),
        .o_nrst(nrst)
    );

    // Leds
    assign o_leds = instrtypes[System_Itype] ? 8'hff : {3'b000, {5'b1 << state}};
    assign TXD  = 1'b0; // not used for now


    // Testbench

    `ifdef TESTBENCH   
        integer     i;
        initial begin
            for(i=0; i<32; ++i) begin
            REGISTERBANK[i] = 0;
            end
        end
        always @(posedge clk) begin
            if (state) $display("x%0d <= %b",rd,wrDATA);
            case (1'b1)
            instrtypes[ALU_Rtype]:      $display(
                                            "PC=%0d // ALUreg rd=%d rs1=%d rs2=%d funct3=%b instr=%b",
                                            PC, rd, rs1, rs2, funct3, instr
                                        );
            instrtypes[ALU_Itype]:      $display(
                                            "PC=%0d // ALUimm rd=%d rs1=%d rs2=%d funct3=%b state=%d",
                                            PC, rd, rs1, rs2, funct3, state
                                         );
            instrtypes[Load_Itype]:     $display("PC=%0d // Load // LEDS = %b", PC, o_leds);
            instrtypes[Store_Stype]:    $display("PC=%0d // Store // LEDS = %b", PC, o_leds);
            instrtypes[Branch_Btype]:    $display("PC=%0d // BRANCH rs1=%0d rs2=%0d", PC,rs1, rs2);
            instrtypes[JAL_Jtype]:      $display("PC=%0d // JAL // LEDS = %b", PC, o_leds);
            instrtypes[JALR_Itype]:     $display("PC=%0d // JALR // LEDS = %b", PC, o_leds);	
            instrtypes[LUI_Utype]:      $display("PC=%0d // LUI // LEDS = %b", PC, o_leds);
            instrtypes[AUIPC_Utype]:    $display("PC=%0d // AUIPC // LEDS = %b", PC, o_leds);
            instrtypes[System_Itype]:   $display("PC=%0d // SYSTEM // LEDS = %b", PC, o_leds);
            endcase 
        end
    `endif

endmodule