module blink_led
(
    input clk,
    output [7:0] led
);

localparam WAIT_TIME = 9000000;
reg [7:0] ledCounter = 0;
reg [23:0] clockCounter = 0;

always @(posedge clk) begin
    clockCounter <= clockCounter + 1;
    if (clockCounter == WAIT_TIME) begin
        clockCounter <= 0;
        ledCounter <= ledCounter + 1;
    end
end

assign led = ledCounter;
endmodule
