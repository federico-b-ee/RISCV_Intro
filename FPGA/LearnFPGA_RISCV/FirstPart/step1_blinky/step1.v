module SOC (
    input  i_clk,        
    input  i_rst,      
    output [3:0] o_leds, 
    input  RXD,        
    output TXD         
);

reg [3:0] count = 0;
always @(posedge i_clk) begin
    count <= count + 1;
end
assign o_leds = count;
assign TXD  = 1'b0; // not used for now

endmodule