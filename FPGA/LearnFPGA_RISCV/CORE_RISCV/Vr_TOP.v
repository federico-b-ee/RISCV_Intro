`include "Vr_ClockDivider.vh"
`include "Vr_RV32I_Processor.vh"

module SOC #(
    LEDS = 3,
    CLK_DIV = 26
) (
    input i_clk,
    output [LEDS-1:0] o_leds
);

  //
  wire [31:0] IO_MEM_rdata, IO_MEM_addr, IO_MEM_wdata;
  wire IO_MEM_wr;

  wire [11:0] IO_wordaddr = IO_MEM_addr[13:2];

  // ClockDivider
  wire clk;
  Vr_ClockDivider #(.DIV(5)) CLK (
      .o_clk(clk),
      .i_clk(i_clk)
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
