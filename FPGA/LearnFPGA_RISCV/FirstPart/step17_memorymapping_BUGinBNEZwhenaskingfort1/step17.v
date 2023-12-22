`include "Vr_CLockDivider.v"
`include "Vr_Memory.v"
`include "Vr_RV32I_Processor.v"
`include "Vr_corescore_emitter_uart.v"

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
        .o_MEM_wdata(MEM_wdata),
        .o_wMASK(MEM_wmask),
        .i_nrst(1'b1)
    );

    //
    wire rEN;
    wire [31:0] MEM_rdata, MEM_addr, MEM_wdata, RAM_rdata;
    wire [3:0] MEM_wmask;

    wire [29:0] MEM_wordaddr = MEM_addr[31:2];

    wire isIO = MEM_addr[22];
    wire isRAM = !isIO;
    wire EN_IO = | MEM_wmask; 
    //

    // RAM
    Vr_Memory Memory (
        .i_addr(MEM_addr),
        .i_clk(clk),
        .i_rEN(rEN & isRAM),
        .i_wdata(MEM_wdata),
        .i_wmask({4{isRAM}} & MEM_wmask),
        .o_rdata(RAM_rdata)
    );

    // ClockDivider
    wire clk;

    Vr_ClockDivider #(.DIV(16)) CLK (
        .o_clk(clk),
        .i_clk(i_clk)
        //.i_rst(rst),
        //.o_nrst(nrst)
    );

    // UART
    localparam IO_UART_DAT_bit  = 1; // W send data (8 bits) 
    localparam IO_UART_CNTL_bit = 2; // R status. bit 9: busy sending

    wire EN_UART = isIO & EN_IO & MEM_wordaddr[IO_UART_DAT_bit];
    wire ready_UART;

    Vr_corescore_emitter_uart #(
        .clk_freq_hz(`BOARD_FREQ*1000000),
        .baud_rate(115200)			    
    ) UART(
        .i_clk(clk),
        .i_rst(1'b0),
        .i_data(MEM_wdata[7:0]),
        .i_valid(EN_UART),
        .o_ready(ready_UART),
        .o_uart_tx(TXD)      			       
    );
    
    wire [31:0] IO_rdata = MEM_wordaddr[IO_UART_CNTL_bit] ? {22'b0, !ready_UART, 9'b0} : 32'b0;

    assign MEM_rdata = isRAM ? RAM_rdata : IO_rdata;

    `ifdef TESTBENCH
        always @(posedge clk) begin
            if(EN_UART) begin
            $write("%c", MEM_wdata[7:0]);
            $fflush(32'h8000_0001);
            end
        end
    `endif  

    // Leds

    localparam IO_LEDS_bit = 0;     // W 1byte(LSByte) (8 leds)
    reg [8:0] Hw_LEDS;
    always @(posedge clk) begin
        if(isIO & EN_IO & MEM_wordaddr[IO_LEDS_bit]) begin
        Hw_LEDS <= MEM_wdata[LEDS-1:0]; // The processor sends write data to a mem_addr. if the addr is above a threshold it's treated as a peripheral?
        end
    end
    assign o_leds = Hw_LEDS;


endmodule