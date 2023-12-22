`include "Vr_CLockDivider.v"

module SOC (
    input  [2:0] i_key,            
    output [2:0] o_leds  
);

    assign o_leds = i_key;
endmodule
