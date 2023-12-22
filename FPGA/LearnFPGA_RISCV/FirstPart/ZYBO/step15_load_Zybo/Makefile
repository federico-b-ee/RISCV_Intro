#--------------------------------
# Xilinx w openFPGALoader Toolchain
#--------------------------------


VIVADO_SCRIPT_PATH = ./media/apps/Xilinx/Vivado/2023.1/settings64.sh

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

fpgaload: ZYBO_RISCV.bit
	openFPGALoader -b zybo_z7_10 ZYBO_RISCV.bit
	
	
