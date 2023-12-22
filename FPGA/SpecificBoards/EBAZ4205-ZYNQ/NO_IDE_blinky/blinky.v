`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/03/2023 04:56:50 PM
// Design Name: 
// Module Name: blinky
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module blinky(
    input  i_clk,   
    output [2:0] o_leds
    );
    reg [25-1:0] counter = 0;
    
    always @(posedge i_clk) begin
    counter <= counter + 1;
    end
    
    assign clk = counter[25-1];

    reg [2:0] count = 0;
    always @(posedge clk) begin
        count <= count + 1;
    end
    assign o_leds = count;
endmodule
