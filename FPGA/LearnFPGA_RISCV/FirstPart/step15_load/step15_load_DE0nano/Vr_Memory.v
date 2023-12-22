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

        // Note: index 100 (word address)
        //     corresponds to 
        // address 400 (byte address)
        MEM[100] = {8'h4, 8'h3, 8'h2, 8'h1};
        MEM[101] = {8'h8, 8'h7, 8'h6, 8'h5};
        MEM[102] = {8'hc, 8'hb, 8'ha, 8'h9};
        MEM[103] = {8'hff, 8'hf, 8'he, 8'hd};            
   end


    
    always @(posedge i_clk) begin
        if(i_rEN) begin 
            o_rdata <= MEM[i_addr[31:2]];
        end
    end
endmodule