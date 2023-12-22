`include "Vr_CLockDivider.v"

module SOC #(parameter N = 4, M = 4) (
    input  i_clk,        
    input  i_rst,      
    output [N-1:0] o_leds, 
    input  RXD,        
    output TXD         
);

    wire clk, nrst, rst;

    Vr_ClockDivider #(.DIV(20)) CLK (
        .o_clk(clk),
        .i_clk(i_clk),
        .i_rst(rst),
        .o_nrst(nrst)
    );

    reg [N-1:0] MEM [M-1:0];
    reg [N-1:0] PC = 0;

    initial begin
        MEM[0]  = 4'b0001;
        MEM[1]  = 4'b0010;
        MEM[2]  = 4'b0100;
        MEM[3]  = 4'b1000;
    end


    reg [N-1:0] count = 0;
    always @(posedge clk) begin
        count <= MEM[PC];
        PC <= (PC==M-1) ? 0 : (PC+1);
    end


    assign o_leds = count;
    assign TXD  = 1'b0; // not used for now

endmodule