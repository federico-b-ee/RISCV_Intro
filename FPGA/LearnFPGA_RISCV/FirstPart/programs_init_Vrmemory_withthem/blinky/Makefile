PROGRAM := blinky
OUTPUT := blinky
all:
	riscv64-linux-gnu-as -march=rv32i -mabi=ilp32 $(PROGRAM).s -o $(PROGRAM).o
	riscv64-linux-gnu-objcopy -O binary $(PROGRAM).o $(PROGRAM).bin
	hexdump  -ve '1/4 "%08x\n"' $(PROGRAM).bin > $(PROGRAM).mem

clean: 
	rm -rf *.o *.bin *.mem