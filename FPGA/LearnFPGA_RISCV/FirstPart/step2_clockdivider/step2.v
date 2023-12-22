`include "Vr_CLockDivider.v"

module SOC (
    input  i_clk,        
    input  i_rst,      
    output [3:0] o_leds, 
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

    reg [3:0] count = 0;
    always @(posedge clk) begin
        count <= count + 1;
    end
    assign o_leds = count;
    assign TXD  = 1'b0; // not used for now

endmodule