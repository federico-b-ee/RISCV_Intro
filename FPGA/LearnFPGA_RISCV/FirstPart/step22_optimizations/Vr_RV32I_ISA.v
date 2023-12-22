module Vr_RV32I_ISA (
    input  [31:0] i_instr,
    output [31:0] o_imm,
    output [ 2:0] o_funct3,
    output [ 6:0] o_funct7,
    output [ 9:0] o_instrtypes,
    output [ 4:0] o_rs1,
    o_rs2,
    o_rd
);

  wire ALU_Rtype = (i_instr[6:0] == 7'b0110011);  //bit0
  wire ALU_Itype = (i_instr[6:0] == 7'b0010011);  //bit1
  wire Load_Itype = (i_instr[6:0] == 7'b0000011);  //bit2
  wire Store_Stype = (i_instr[6:0] == 7'b0100011);  //bit3
  wire Branch_Btype = (i_instr[6:0] == 7'b1100011);  //bit4
  wire JAL_Jtype = (i_instr[6:0] == 7'b1101111);  //bit5
  wire JALR_Itype = (i_instr[6:0] == 7'b1100111);  //bit6
  wire LUI_Utype = (i_instr[6:0] == 7'b0110111);  //bit7
  wire AUIPC_Utype = (i_instr[6:0] == 7'b0010111);  //bit8
  wire System_Itype = (i_instr[6:0] == 7'b1110011);  //bit9


  wire [31:0] imm_Itype = {{21{i_instr[31]}}, i_instr[30:20]};
  wire [31:0] imm_Stype = {{21{i_instr[31]}}, i_instr[30:25], i_instr[11:7]};
  wire [31:0] imm_Btype = {{20{i_instr[31]}}, i_instr[7], i_instr[30:25], i_instr[11:8], 1'b0};
  wire [31:0] imm_Jtype = {{12{i_instr[31]}}, i_instr[19:12], i_instr[20], i_instr[30:21], 1'b0};
  wire [31:0] imm_Utype = {i_instr[31:12], {12{1'b0}}};

  assign o_imm = (ALU_Itype || Load_Itype || JALR_Itype || System_Itype)
         ? imm_Itype
         : (Store_Stype)
         ? imm_Stype
         : (Branch_Btype)
         ? imm_Btype
         : (JAL_Jtype)
         ? imm_Jtype
         : (AUIPC_Utype || LUI_Utype)
         ? imm_Utype
         : 32'h0000_0000;

  assign o_rs1 = i_instr[19:15];
  assign o_rs2 = i_instr[24:20];
  assign o_rd = i_instr[11:7];

  assign o_funct3 = i_instr[14:12];
  assign o_funct7 = i_instr[31:25];

  assign o_instrtypes = {
    System_Itype,
    AUIPC_Utype,
    LUI_Utype,
    JALR_Itype,
    JAL_Jtype,
    Branch_Btype,
    Store_Stype,
    Load_Itype,
    ALU_Itype,
    ALU_Rtype
  };


endmodule
