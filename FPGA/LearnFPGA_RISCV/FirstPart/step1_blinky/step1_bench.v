module bench();
   reg clk;
   wire rst = 0; 
   wire [3:0] leds;
   reg  RXD = 1'b0;
   wire TXD;

   SOC uut(
     .i_clk(clk),
     .i_rst(rst),
     .o_leds(leds),
     .RXD(RXD),
     .TXD(TXD)
   );
   
   reg[4:0] prev_leds = 0;

   initial begin
      clk = 0;
   end
   always begin        
      #4.9	clk = 1; // half timescale on
      #5		clk = 0; //	half timescale off    
      #0.1;          // some delay       
   end


   always @(posedge clk)begin 
	 if(leds != prev_leds) begin
	    $display("LEDS = %b",leds);
	 end
	 prev_leds <= leds;
   end

endmodule 