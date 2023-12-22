`include "Vr_CLockDivider.v"
`include "Vr_Memory.v"
`include "Vr_RV32I_Processor.v"


module SOC #(parameter N = 32, M = 5, LEDS = 8) (
    input  i_clk,        
    input  i_rst,      
    output [LEDS-1:0] o_leds, 
    input  RXD,        
    output TXD         
);

    // Processor 
    Vr_RV32I_Processor Processor (
        .i_clk(clk),
        .i_MEM_rdata(MEM_rdata),
        .o_MEM_addr(MEM_addr),
        .o_rEN(rEN),
        .o_x1(o_x1),
        .o_MEM_wdata(MEM_wdata),
        .o_wMASK(MEM_wmask),
        .i_nrst(1'b1)
    );

    //
    wire rEN;
    wire [31:0] MEM_rdata, MEM_addr, MEM_wdata, o_x1;
    wire [3:0] MEM_wmask;
    //

    // RAM
    Vr_Memory Memory (
        .i_addr(MEM_addr),
        .i_clk(clk),
        .i_rEN(rEN),
        .i_wdata(MEM_wdata),
        .i_wmask(MEM_wmask),
        .o_rdata(MEM_rdata)
    );

    // ClockDivider
    wire clk;

    Vr_ClockDivider #(.DIV(19)) CLK (
        .o_clk(clk),
        .i_clk(i_clk)
        //.i_rst(rst),
        //.o_nrst(nrst)
    );

    // Leds
    assign o_leds = o_x1[LEDS-1:0];

    assign TXD  = 1'b0; // not used for now

endmodule