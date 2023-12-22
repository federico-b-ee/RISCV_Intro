module Vr_Memory (
    input i_clk,
    input [31:0] i_addr,
    output reg [31:0] o_rdata,
    input i_rEN
);

    reg[31:0] MEM [255:0];
    // RAM
    `include "riscv_assembly.v"

    integer L0_=4;
    initial begin
        ADD(x1,x0,x0);
        Label(L0_);
        ADDI(x1,x1,1);
        JAL(x0,LabelRef(L0_));
        EBREAK();
        endASM();
    end
    
    always @(posedge i_clk) begin
        if(i_rEN) begin 
            o_rdata <= MEM[i_addr[31:2]];
        end
    end
endmodule