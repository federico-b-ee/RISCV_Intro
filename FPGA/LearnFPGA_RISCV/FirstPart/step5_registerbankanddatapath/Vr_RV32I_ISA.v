module Vr_RV32I_ISA (
    input [31:0] i_instr,
    output [31:0] o_imm_Itype, 
    output [31:0] o_imm_Stype, 
    output [31:0] o_imm_Btype, 
    output [31:0] o_imm_Jtype, 
    output [31:0] o_imm_Utype,
    output [2:0] o_funct3,
    output [6:0] o_funct7,
    output o_ALU_Rtype, o_ALU_Itype, o_AUIPC_Utype, o_Branch_Btype, o_Load_Itype, o_Store_Stype, o_System_Itype, o_LUI_Utype, o_JAL_Jtype, o_JALR_Itype,
    output [4:0] o_rs1, o_rs2, o_rd
);

    assign o_ALU_Rtype       =   (i_instr[6:0] == 7'b0110011);
    assign o_ALU_Itype       =   (i_instr[6:0] == 7'b0010011);
    assign o_Load_Itype      =   (i_instr[6:0] == 7'b0000011);
    assign o_Store_Stype     =   (i_instr[6:0] == 7'b0100011);
    assign o_Branch_Btype    =   (i_instr[6:0] == 7'b1100011);
    assign o_JAL_Jtype       =   (i_instr[6:0] == 7'b1101111);
    assign o_JALR_Itype      =   (i_instr[6:0] == 7'b1100111);
    assign o_LUI_Utype       =   (i_instr[6:0] == 7'b0110111);
    assign o_AUIPC_Utype     =   (i_instr[6:0] == 7'b0010111);
    assign o_System_Itype    =   (i_instr[6:0] == 7'b1110011);


    assign o_imm_Itype = {{21{i_instr[31]}}, i_instr[30:20]};
    assign o_imm_Stype = {{21{i_instr[31]}}, i_instr[30:25], i_instr[11:7]};
    assign o_imm_Btype = {{20{i_instr[31]}}, i_instr[7], i_instr[30:25], i_instr[11:8], 1'b0};
    assign o_imm_Jtype = {{12{i_instr[31]}}, i_instr[19:12], i_instr[20], i_instr[30:21], 1'b0};
    assign o_imm_Utype = {i_instr[31:12], {12{1'b0}}};
    
    assign o_rs1 = i_instr[19:15];
    assign o_rs2 = i_instr[24:20];
    assign o_rd  = i_instr[11:7];

    assign funct3 = i_instr[14:12];
    assign funct7 = i_instr[31:25];

    
endmodule