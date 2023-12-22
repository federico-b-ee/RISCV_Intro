module Vr_ALU (
    input [31:0] i_in1, i_in2,
    input [31:0] i_instr,
    output [31:0] o_out, 
    output o_EQ, o_LT, o_LTU,
    output [31:0] o_ALUadd

);

    // The shifter can be optimized more 
    wire [4:0] shamt = (i_instr[5]) ? i_in2[4:0] : i_instr[24:20]; // shift up to 32 positions  

    wire [2:0] funct3 = i_instr[14:12];
    wire [6:0] funct7 = i_instr[31:25];

    reg [31:0] ALUoutput;

    // It can be done with one adder. In this way, it is more self-explanatory
    wire [32:0] ALUsub = {1'b0, i_in1} + {1'b1, ~i_in2} + 33'b1;
    wire [31:0] ALUadd = i_in1 + i_in2;

    wire EQ  = (ALUsub[31:0] == 0);
    wire LTU = ALUsub[32];
    wire LT  = (i_in1[31] ^ i_in2[31]) ? i_in1[31] : ALUsub[32];

    always @(*) begin
        ALUoutput = 32'h0;  // Initialize with default value
        case (funct3)
            3'h0: ALUoutput = (funct7[5] & i_instr[5]) ? ALUsub[31:0] : ALUadd; // add
            3'h1: ALUoutput = i_in1 << shamt;   // sll
            3'h2: ALUoutput = {31'b0, LT};  // slt
            3'h3: ALUoutput = {31'b0, LTU};  // sltu
            3'h4: ALUoutput = (i_in1 ^ i_in2);  // xor
            3'h5: ALUoutput = (funct7[5] & i_instr[5]) ? (i_in1 >>> shamt) : (i_in1 >> shamt);  // srl
            3'h6: ALUoutput = (i_in1 | i_in2);  // or
            3'h7: ALUoutput = (i_in1 & i_in2);  // and
        endcase
    end

    assign {o_EQ, o_LT, o_LTU} = {EQ, LT, LTU};
    assign o_ALUadd = ALUadd;

    assign o_out = ALUoutput;

endmodule