module Vr_Memory (
    input i_clk,
    input [31:0] i_addr,
    output reg [31:0] o_rdata,
    input i_rEN
);

    reg[31:0] MEM [255:0];
    // RAM

    initial begin 
        $readmemh("test.mem", MEM);
    end

    
    always @(posedge i_clk) begin
        if(i_rEN) begin 
            o_rdata <= MEM[i_addr[31:2]];
        end
    end
endmodule