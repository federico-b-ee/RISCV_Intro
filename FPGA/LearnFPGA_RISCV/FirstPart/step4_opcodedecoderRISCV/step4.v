`include "Vr_CLockDivider.v"
`include "Vr_RV32I_ISA.v"

module SOC #(parameter N = 32, M = 5, LEDS = 8) (
    input  i_clk,        
    input  i_rst,      
    output [LEDS-1:0] o_leds, 
    input  RXD,        
    output TXD         
);

    reg [N-1:0] MEM [M-1:0];
    reg [N-1:0] PC = 0;
    reg [31:0] instr; 

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
        .o_System_Itype(System_Itype)
    );


    wire clk, nrst, rst;

    Vr_ClockDivider #(.DIV(20)) CLK (
        .o_clk(clk),
        .i_clk(i_clk),
        .i_rst(rst),
        .o_nrst(nrst)
    );

    reg [N-1:0] PC_prev = 0;
    always @(posedge clk) begin
        instr <= MEM[PC];
        PC_prev <= PC;
        PC <= (PC==M-1) ? 0 : (PC+1);
    end

    assign o_leds = System_Itype ? 8'hff : {3'b000, PC[0], ALU_Rtype, ALU_Itype, Store_Stype, Load_Itype};
    assign TXD  = 1'b0; // not used for now

    `ifdef TESTBENCH   
        always @(posedge clk) begin
            case (1'b1)
            ALU_Rtype:      $display("PC=%0d // ALUreg", PC_prev);
            ALU_Itype:      $display("PC=%0d // ALUimm", PC_prev);
            Load_Itype:     $display("PC=%0d // Load", PC_prev);
            Store_Stype:    $display("PC=%0d // Store", PC_prev);
            Branch_Btype:   $display("PC=%0d // Branch", PC_prev);
            JAL_Jtype:      $display("PC=%0d // JAL", PC_prev);
            JALR_Itype:     $display("PC=%0d // JALR", PC_prev);	
            LUI_Utype:      $display("PC=%0d // LUI", PC_prev);
            AUIPC_Utype:    $display("PC=%0d // AUIPC", PC_prev);
            System_Itype:   $display("PC=%0d // SYSTEM", PC_prev);
            endcase 
        end
    `endif

endmodule