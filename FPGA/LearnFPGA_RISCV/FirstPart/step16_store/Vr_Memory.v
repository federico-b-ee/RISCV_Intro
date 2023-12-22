module Vr_Memory (
    input i_clk,
    input [31:0] i_addr,
    output reg [31:0] o_rdata,
    input i_rEN,
    input [31:0] i_wdata,
    input [3:0] i_wmask
);

    reg[31:0] MEM [255:0];
    // RAM

    wire [29:0] ADDR = i_addr[31:2];
   

    `ifdef TESTBENCH
    localparam slow_bit=0;
    `else
    localparam slow_bit=0;
    `endif
    
    `include "riscv_assembly.v"
    integer L0_   = 12;
    integer L1_   = 40;
    integer wait_ = 64;   
    integer L2_   = 72;
    
    initial begin

        LI(a0,0);
    // Copy 16 bytes from adress 400
    // to address 800
        LI(s1,1);      
        LI(s0,0);         
    Label(L0_); 
        LB(a1,s0,400);
        SB(a1,s0,800);       
        CALL(LabelRef(wait_));
        ADDI(s0,s0,1); 
        BNE(s0,s1, LabelRef(L0_));

    // Read 16 bytes from adress 800
        LI(s0,0);
    Label(L1_);
        LB(a0,s0,800); // a0 (=x10) is plugged to the LEDs
        CALL(LabelRef(wait_));
        ADDI(s0,s0,1); 
        BNE(s0,s1, LabelRef(L1_));
        EBREAK();
        
    Label(wait_);
        LI(t0,1);
        SLLI(t0,t0,slow_bit);
    Label(L2_);
        ADDI(t0,t0,-1);
        BNEZ(t0,LabelRef(L2_));
        RET();

        endASM();

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
                o_rdata <= MEM[ADDR];
            end

            if (i_wmask[0]) MEM[ADDR][7:0] <= i_wdata[7:0];
            if (i_wmask[1]) MEM[ADDR][15:8] <= i_wdata[15:8];
            if (i_wmask[2]) MEM[ADDR][23:16] <= i_wdata[23:16];
            if (i_wmask[3]) MEM[ADDR][31:24] <= i_wdata[31:24];
        end
endmodule