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
   integer    L0_      = 12;
   integer    L1_      = 20;
   integer    L2_      = 52;      
   integer    wait_    = 104;
   integer    wait_L0_ = 112;
   integer    putc_    = 124; 
   integer    putc_L0_ = 132;
   
   initial begin
      LI(sp,32'h1800);   // End of RAM, 6kB
      LI(gp,32'h400000); // IO page

   Label(L0_);

      // Count from 0 to 15 on the LEDs      
      LI(s0,3); // upper bound of loop
      LI(a0,0);
   Label(L1_);
      SW(a0,gp,IO_BIT_TO_OFFSET(IO_LEDS_bit));
      CALL(LabelRef(wait_));
      ADDI(a0,a0,1);
      BNE(a0,s0,LabelRef(L1_));

      // Send abcdef...xyz to the UART
      LI(s0,26); // upper bound of loop     
      LI(a0,"a");
      LI(s1,0);
   Label(L2_);
      CALL(LabelRef(putc_));
      ADDI(a0,a0,1);
      ADDI(s1,s1,1);
      BNE(s1,s0,LabelRef(L2_));

      // CR;LF
      LI(a0,13);
      CALL(LabelRef(putc_));
      LI(a0,10);
      CALL(LabelRef(putc_));
      
      J(LabelRef(L0_));
      
      EBREAK(); // I systematically keep it before functions
                // in case I decide to remove the loop...

   Label(wait_);
      LI(t0,1);
      SLLI(t0,t0,slow_bit);
   Label(wait_L0_);
      ADDI(t0,t0,-1);
      BNEZ(t0,LabelRef(wait_L0_));
      RET();

   Label(putc_);
      // Send character to UART
      SW(a0,gp,IO_BIT_TO_OFFSET(IO_UART_DAT_bit));
      // Read UART status, and loop until bit 9 (busy sending)
      // is zero.
      LI(t0,1<<9);
   Label(putc_L0_);
      LW(t1,gp,IO_BIT_TO_OFFSET(IO_UART_CNTL_bit));     
      AND(t1,t1,t0);
      BNEZ(t1,LabelRef(putc_L0_));
      RET();
	   
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