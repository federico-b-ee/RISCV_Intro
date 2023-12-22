module Vr_Memory (
    input i_clk,
    input [31:0] i_addr,
    output reg [31:0] o_rdata,
    input i_rEN,
    input [31:0] i_wdata,
    input [3:0] i_wmask
);
    // Peripherals

    localparam IO_LEDS_bit = 0; // W 1byte(LSByte) (8 leds)
    localparam IO_UART_DAT_bit  = 1; // W send data (8 bits) 
    localparam IO_UART_CNTL_bit = 2; // R status. bit 9: busy sending

    function [31:0] IO_BIT_TO_OFFSET;
        input [31:0] peripheral;// upto 20 peripherals
        begin
           IO_BIT_TO_OFFSET = 1 << (peripheral + 2); 
        end
    endfunction




    // RAM
    reg[31:0] MEM [1535:0];// 1536 4-bytes words = 6 Kb of RAM in total


    wire [29:0] ADDR = i_addr[31:2];
   

`ifdef TESTBENCH
   localparam slow_bit=1;
`else
   localparam slow_bit=1;
`endif
   
`include "riscv_assembly.v"
   integer    L0_ = 64; 
   integer    L1_ = 72;
   
   initial begin
      LI(sp,32'h1800); //4  // End of RAM, 6kB
      LI(gp,32'h400000);//8 // IO page
      // Send abcdef...xyz to the UART
      LI(s0,1); //12 
      LI(a0,"a"); //16
      LI(s1,0); //20
      CALL(LabelRef(L0_)); //24 y 28
      ADDI(a0,a0,1); //32
      ADDI(s1,s1,1); //36
      // CR;LF
      LI(a0,13); //40
      CALL(LabelRef(L0_)); //44 y 48
      LI(a0,10); //52
      CALL(LabelRef(L0_)); //56 y 60
      
   Label(L0_); //64
      // Send character to UART
      SW(a0,gp,IO_BIT_TO_OFFSET(IO_UART_DAT_bit));
      LI(t0,1<<9); //68
   Label(L1_); //72
      LW(t1,gp,IO_BIT_TO_OFFSET(IO_UART_CNTL_bit));     
      AND(t1,t1,t0); //76
      BNEZ(t1,L1_); //80
      RET(); //84
	   
      endASM(); 
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