`include "Vr_CLockDivider.v"
`include "Vr_Memory.v"
`include "Vr_RV32I_Processor.v"


module SOC #(parameter N = 32, M = 5, LEDS = 4) (
    input  i_clk,          
    output [LEDS-1:0] o_leds      
);

    // Processor 
    Vr_RV32I_Processor Processor (
        .i_clk(clk),
        .i_MEM_rdata(MEM_rdata),
        .o_MEM_addr(MEM_addr),
        .o_rEN(rEN),
        .o_x1(o_x1),
        .i_nrst(1'b1)
    );

    //
    wire rEN;
    wire [31:0] MEM_rdata, MEM_addr, o_x1;
    //

    // RAM
    Vr_Memory Memory (
        .i_addr(MEM_addr),
        .i_clk(clk),
        .i_rEN(rEN),
        .o_rdata(MEM_rdata)
    );

    // ClockDivider
    wire clk;

    Vr_ClockDivider #(.DIV(20)) CLK (
        .o_clk(clk),
        .i_clk(i_clk)
    );

    // Leds
    assign o_leds = o_x1[LEDS-1:0];

endmodule