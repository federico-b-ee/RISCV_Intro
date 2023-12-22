module Vr_ClockDivider #(parameter DIV = 20) (
    input   i_clk,
    output  o_clk
    //input   i_rst,
    //output  o_nrst
);
// if i_clk = 50Mhz -> o_clk = i_clk / 2^DIV =(approx) 50Hz if DIV = 20.

  reg [DIV-1:0] counter = 0;

  always @(posedge i_clk) begin
    counter <= counter + 1;
  end

  assign o_clk = counter[DIV-1];
endmodule