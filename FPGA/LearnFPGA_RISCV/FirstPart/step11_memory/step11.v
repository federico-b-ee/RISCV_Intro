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
        .o_x1(x1)
    );

    //
    wire rEN;
    wire [31:0] MEM_rdata, MEM_addr, x1;
    //

    // RAM
    Vr_Memory Memory (
        .i_addr(MEM_addr),
        .i_clk(clk),
        .i_rEN(rEN),
        .o_rdata(MEM_rdata)
    );

    // ClockDivider
    wire clk, nrst, rst;

    Vr_ClockDivider #(.DIV(20)) CLK (
        .o_clk(clk),
        .i_clk(i_clk),
        .i_rst(rst),
        .o_nrst(nrst)
    );

    // Leds
    assign o_leds = x1[LEDS-1:0];
    assign TXD  = 1'b0; // not used for now


    `ifdef TESTBENCH   
        always @(posedge clk) begin
            $display("x1 <= %b",o_leds);
        end
    `endif 

endmodule