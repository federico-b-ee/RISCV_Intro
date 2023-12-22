YOSYS ?= yosys
NEXTPNR ?= nextpnr-gowin
openFPGALoader ?= openFPGALoader
TARGET ?= blinky

.DEFAULT_GOAL := help


help:
	@echo "Makefile Help:"
	@echo "  make                          	: Show this help message (default)"
	@echo "  make build TARGET=<filename.v>	: Compile the code and generate the output file"
	@echo "  make clean                    	: Remove generated JSON files"
	@echo "  make purge                    	: Remove generated JSON and .fs files"
	@echo "  make flash                    	: Flash the generated .fs file onto the Tang Nano 9K board"
	@echo ""
	@echo "Variables:"
	@echo "  YOSYS            		: Yosys tool path (default: yosys)"
	@echo "  NEXTPNR          		: Nextpnr tool path (default: nextpnr-gowin)"
	@echo "  openFPGALoader   		: openFPGALoader tool path (default: openFPGALoader)"
	@echo "  TARGET           		: Target name (default: blinky)"



build: $(TARGET)-tangnano9k.fs


.PHONY: clean build purge flash

clean: 
	rm -f *.json 

purge:
	rm -f *.fs *.json
	
flash: build
	$(openFPGALoader) -m -b tangnano9k $(TARGET)-tangnano9k.fs
	

$(TARGET)-tangnano9k.fs: $(TARGET)-tangnano9k.json
	gowin_pack -d GW1N-9C -o $@ $^

$(TARGET)-tangnano9k.json: $(TARGET)-tangnano9k-synth.json tangnano9k.cst
	$(NEXTPNR) --json $< --write $@ --device GW1NR-LV9QN88PC6/I5 --family GW1N-9C --cst tangnano9k.cst


$(TARGET)-tangnano9k-synth.json: $(TARGET).v
	$(YOSYS) -D LEDS_NR=6 -D OSC_TYPE_OSC -p "read_verilog $^; synth_gowin -json $@"



	
