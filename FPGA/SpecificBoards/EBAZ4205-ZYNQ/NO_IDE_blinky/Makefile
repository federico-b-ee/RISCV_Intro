#--------------------------------
# Xilinx w openFPGALoader Toolchain
#--------------------------------


VIVADO_SCRIPT_PATH = /tools/Xilinx/Vivado/2023.1/settings64.sh

#--------------------------------
# Bitstream
#--------------------------------

all:
	$(shell $(VIVADO_SCRIPT_PATH))
	vivado -mode batch -nolog -nojournal -source build.tcl 

clean:
	rm -rf *.log *.jou .Xil/

#--------------------------------
# Flash
#--------------------------------

fpgaload: EBAZ4205_blinky.bit
	openFPGALoader -d /dev/ttyUSB0 EBAZ4205_button.bit
	
	
