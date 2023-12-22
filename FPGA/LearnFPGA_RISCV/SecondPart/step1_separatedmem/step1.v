`include "Vr_CLockDivider.v"
`include "Vr_RV32I_Processor.v"
`include "Vr_corescore_emitter_uart.v"

module SOC #(
    parameter N = 32,
    LEDS = 3
) (
    input i_clk,
    input i_rst,
    output [LEDS-1:0] o_leds,
    input RXD,
    output TXD
);

  // Processor
  Vr_RV32I_Processor Processor (
      .i_clk(clk),
      .i_IO_MEM_rdata(IO_MEM_rdata),
      .o_IO_MEM_addr(IO_MEM_addr),
      .o_IO_MEM_wr(IO_MEM_wr),
      .o_IO_MEM_wdata(IO_MEM_wdata),
      .i_nrst(1'b1)
  );

  //
  wire [31:0] IO_MEM_rdata, IO_MEM_addr, IO_MEM_wdata;
  wire IO_MEM_wr;

  wire [11:0] IO_wordaddr = IO_MEM_addr[13:2];

  // ClockDivider
  wire clk = i_clk;

  /*     Vr_ClockDivider #(.DIV(1)) CLK (
          .o_clk(clk),
          .i_clk(i_clk)
          //.i_rst(rst),
          //.o_nrst(nrst)
      ); */
/* 
  // UART
  localparam IO_UART_DAT_bit = 1;  // W send data (8 bits)
  localparam IO_UART_CNTL_bit = 2;  // R status. bit 9: busy sending

  wire EN_UART = IO_MEM_wr & IO_wordaddr[IO_UART_DAT_bit];
  wire ready_UART;

  Vr_corescore_emitter_uart #(
      .clk_freq_hz(`CPU_FREQ * 1000000),
      .baud_rate  (1000000)
  ) UART (
      .i_clk(clk),
      .i_rst(1'b0),
      .i_data(IO_MEM_wdata[7:0]),
      .i_valid(EN_UART),
      .o_ready(ready_UART),
      .o_uart_tx(TXD)
  );

  assign IO_MEM_rdata = IO_wordaddr[IO_UART_CNTL_bit] ? {22'b0, !ready_UART, 9'b0} : 32'b0;//!ready_UART goes in the middle

`ifdef TESTBENCH

  always @(posedge clk) begin
    if (EN_UART) begin
      $write("%c", IO_MEM_wdata[7:0]);
      $fflush(32'h8000_0001);
    end
  end
`endif */

  // Leds
  localparam IO_LEDS_bit = 0;  // W 1byte(LSByte) (8 leds)
  reg [LEDS-1:0] Hw_LEDS;
  always @(posedge clk) begin
    if (IO_MEM_wr & IO_wordaddr[IO_LEDS_bit]) begin
      Hw_LEDS <= IO_MEM_wdata[LEDS-1:0]; // The processor sends write data to a mem_addr. if the addr is above a threshold it's treated as a peripheral?

`ifdef TESTBENCH
      $display("LEDS:%b", Hw_LEDS);
`endif

    end
  end

  assign o_leds = Hw_LEDS;
endmodule
