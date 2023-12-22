`include "Vr_CLockDivider.v"
`include "Vr_RV32I_ISA.v"

module SOC #(parameter N = 32, M = 5, LEDS = 8) (
    input  i_clk,        
    input  i_rst,      
    output [LEDS-1:0] o_leds, 
    input  RXD,        
    output TXD         
);

    reg [N-1:0] PC = 0;
    reg [31:0] instr; 

    // Register Bank
    reg [31:0] REGISTERBANK [31:0];
    reg [31:0] register_rs1;
    reg [31:0] register_rs2;
    reg [31:0] register_rd;
    
    // Memory
    reg [N-1:0] MEM [M-1:0];

    initial begin
      // add x1, x0, x0
      //                    rs2   rs1  add  rd  ALUREG
      MEM[0] = 32'b0000000_00000_00000_000_00001_0110011;
      // addi x1, x1, 1
      //             imm         rs1  add  rd   ALUIMM
      MEM[1] = 32'b000000000001_00001_000_00001_0010011;
      // lw x2,0(x1)
      //             imm         rs1   w   rd   LOAD
      MEM[2] = 32'b000000000000_00001_010_00010_0000011;
      // sw x2,0(x1)
      //             imm   rs2   rs1   w   imm  STORE
      MEM[3] = 32'b000000_00001_00010_010_00000_0100011;
      // ebreak
      //                                        SYSTEM
      MEM[4] = 32'b000000000001_00000_000_00000_1110011;
    end


    // RV32I ISA
    wire ALU_Rtype;
    wire ALU_Itype;
    wire Load_Itype;
    wire Store_Stype;
    wire Branch_Btype;
    wire JAL_Jtype;
    wire JALR_Itype;
    wire LUI_Utype;
    wire AUIPC_Utype;
    wire System_Itype;
    wire [4:0] rs1, rs2, rd;
    wire [31:0] imm_Itype, imm_Stype, imm_Btype, imm_Jtype, imm_Utype;
    wire [2:0] funct3;
    wire [6:0] funct7;

    Vr_RV32I_ISA RV32I_ISA (
        .i_instr(instr),
        .o_ALU_Rtype(ALU_Rtype),
        .o_ALU_Itype(ALU_Itype),
        .o_Load_Itype(Load_Itype),
        .o_Store_Stype(Store_Stype),
        .o_Branch_Btype(Branch_Btyp),
        .o_JAL_Jtype(JAL_Jtype),
        .o_JALR_Itype(JALR_Itype),
        .o_LUI_Utype(LUI_Utype),
        .o_AUIPC_Utype(AUIPC_Utype),
        .o_System_Itype(System_Itype),
        .o_rs1(rs1),
        .o_rs2(rs2),
        .o_rd(rd),
        .o_imm_Itype(imm_Itype), 
        .o_imm_Stype(imm_Stype), 
        .o_imm_Btype(imm_Btype), 
        .o_imm_Jtype(imm_Jtype), 
        .o_imm_Utype(imm_Utype),
        .o_funct3(funct3),
        .o_funct7(funct7)
    );

    // Datapath
    parameter FETCH = 0, REGS = 1, EXEC = 2;
    reg [1:0] state = FETCH;


    wire [31:0] wrDATA;
    wire        wrEN;
    assign wrDATA = 0; // for now
    assign wrEN = 0;   // for now

    always @(posedge clk) begin
        case (state)
            FETCH: begin
                instr <= MEM[PC];
                state <= REGS;
            end
            REGS: begin
                register_rs1 = REGISTERBANK[rs1];
                register_rs2 = REGISTERBANK[rs2];
                state <= EXEC;
            end
            EXEC: begin
                if (!System_Itype) begin 
                    PC <= (PC==M-1) ? 0 : (PC+1);
                end
                state <= FETCH;
            end
        endcase
    end

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
    assign o_leds = System_Itype ? 8'hff : {3'b000, {5'b1 << state}};
    assign TXD  = 1'b0; // not used for now


    // Testbench
    `ifdef TESTBENCH   
        always @(posedge clk) begin
            case (1'b1)
            ALU_Rtype:      $display("PC=%0d // ALUreg // LEDS = %b", PC, o_leds);
            ALU_Itype:      $display("PC=%0d // ALUimm // LEDS = %b", PC, o_leds);
            Load_Itype:     $display("PC=%0d // Load // LEDS = %b", PC, o_leds);
            Store_Stype:    $display("PC=%0d // Store // LEDS = %b", PC, o_leds);
            Branch_Btype:   $display("PC=%0d // Branch // LEDS = %b", PC, o_leds);
            JAL_Jtype:      $display("PC=%0d // JAL // LEDS = %b", PC, o_leds);
            JALR_Itype:     $display("PC=%0d // JALR // LEDS = %b", PC, o_leds);	
            LUI_Utype:      $display("PC=%0d // LUI // LEDS = %b", PC, o_leds);
            AUIPC_Utype:    $display("PC=%0d // AUIPC // LEDS = %b", PC, o_leds);
            System_Itype:   $display("PC=%0d // SYSTEM // LEDS = %b", PC, o_leds);
            endcase 
        end
    `endif

endmodule