module blink_led (
	input clk,
	output [8-1:0] led
);

reg [21:0] ctr_q;
wire [21:0] ctr_d;

// Sequential code (flip-flop)
always @(posedge clk)
	ctr_q <= ctr_d;

// Combinational code (boolean logic)
assign ctr_d = ctr_q + 1'b1;
assign led = ctr_q[21:21-(8 - 1)];

endmodule
