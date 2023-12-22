PROJECT ?= step22

# Verilog source files
SRCS := $(PROJECT)_bench.v $(PROJECT).v 

# Name of the output file
OUTPUT := $(PROJECT).o

# Iverilog compiler and flags
IVERILOG := iverilog
IVERILOG_FLAGS := -DTESTBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10

# VVP simulator
VVP := vvp

# Targets
.PHONY: all clean

#iverilog: $(OUTPUT)

$(OUTPUT): $(SRCS)
	$(IVERILOG) $(IVERILOG_FLAGS) -o $(OUTPUT) $(SRCS)

simiv: clean $(OUTPUT)
 
	$(VVP) $(OUTPUT)

clean:
	rm -rf $(OUTPUT) 

remove:
	rm -rf obj_dir

simver: remove
	./run_ver.sh $(PROJECT).v
