module Vr_ALU (
    input [31:0] i_in1, i_in2,
    input [31:0] i_instr,
    output [31:0] o_out

);
    wire [4:0] shamt = (i_instr[5]) ? i_in2[4:0] : i_instr[24:20]; // shift up to 32 positions  

    wire [2:0] funct3 = i_instr[14:12];
    wire [6:0] funct7 = i_instr[31:25];

    reg [31:0] ALUoutput;

    always @(*) begin
        ALUoutput = 32'h0;  // Initialize with default value
        case (funct3)
            3'h0: ALUoutput = (funct7[5] & i_instr[5]) ? (i_in1 - i_in2) : (i_in1 + i_in2);  // add
            3'h1: ALUoutput = i_in1 << shamt;                                                // sll
            3'h2: ALUoutput = ($signed(i_in1) < $signed(i_in2));                             // slt
            3'h3: ALUoutput = (i_in1 < i_in2);                                               // sltu
            3'h4: ALUoutput = (i_in1 ^ i_in2);                                               // xor
            3'h5: ALUoutput = (funct7[5] & i_instr[5]) ? (i_in1 >>> shamt) : (i_in1 >> shamt);  // srl
            3'h6: ALUoutput = (i_in1 | i_in2);                                               // or
            3'h7: ALUoutput = (i_in1 & i_in2);                                               // and
        endcase
    end

    assign o_out = ALUoutput;

endmodule