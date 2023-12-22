PROJECT ?= step2

# Verilog source files
SRCS := $(PROJECT)_bench.v $(PROJECT).v 

# Name of the output file
OUTPUT := $(PROJECT).o

# Iverilog compiler and flags
IVERILOG := iverilog
IVERILOG_FLAGS := -DBENCH -DBOARD_FREQ=10

# VVP simulator
VVP := vvp

# Targets
.PHONY: all clean

all: $(OUTPUT)

$(OUTPUT): $(SRCS)
	$(IVERILOG) $(IVERILOG_FLAGS) -o $(OUTPUT) $(SRCS)

run: $(OUTPUT)
	$(VVP) $(OUTPUT)

clean:
	rm -f $(OUTPUT)
