###################################################################
# Project Configuration:
#
# Specify the name of the design (project) and the Quartus II
# Settings File (.qsf)
###################################################################

PROJECT = step6
TOP_LEVEL_ENTITY = SOC
ASSIGNMENT_FILES = $(PROJECT).qpf $(PROJECT).qsf
QUARTUS_PATH = ~/intelFPGA_lite/22.1std

###################################################################
# Part, Family, Boardfile DE1 or DE2
FAMILY = "Cyclone IV E"
PART = EP4CE22F17C6
BOARDFILE = Pins.tcl
###################################################################

###################################################################
# Setup your sources here
SRCS = ./$(PROJECT).v

###################################################################
# Main Targets
#
# all: build everything
# clean: remove output files and database
# program: program your device with the compiled design
###################################################################

all: clean smart.log $(PROJECT).asm.rpt $(PROJECT).sta.rpt 

clean:
	find . ! \( -name '*.v' -o -name '*.tcl' -o -name '*.sof' -o -name 'Makefile' \) -delete


map: smart.log $(PROJECT).map.rpt
fit: smart.log $(PROJECT).fit.rpt
asm: smart.log $(PROJECT).asm.rpt
sta: smart.log $(PROJECT).sta.rpt
smart: smart.log

###################################################################
# Executable Configuration
###################################################################

MAP_ARGS = --read_settings_files=on $(addprefix --source=,$(SRCS))

FIT_ARGS = --part=$(PART) --read_settings_files=on
ASM_ARGS =
STA_ARGS =

###################################################################
# Target implementations
###################################################################

STAMP = echo done >

$(PROJECT).map.rpt: map.chg $(SOURCE_FILES) 
	$(QUARTUS_PATH)/quartus/bin/quartus_map $(MAP_ARGS) $(PROJECT)
	$(STAMP) fit.chg

$(PROJECT).fit.rpt: fit.chg $(PROJECT).map.rpt
	$(QUARTUS_PATH)/quartus/bin/quartus_fit $(FIT_ARGS) $(PROJECT)
	$(STAMP) asm.chg
	$(STAMP) sta.chg

$(PROJECT).asm.rpt: asm.chg $(PROJECT).fit.rpt
	$(QUARTUS_PATH)/quartus/bin/quartus_asm $(ASM_ARGS) $(PROJECT)

$(PROJECT).sta.rpt: sta.chg $(PROJECT).fit.rpt
	$(QUARTUS_PATH)/quartus/bin/quartus_sta $(STA_ARGS) $(PROJECT)

smart.log: $(ASSIGNMENT_FILES)
	$(QUARTUS_PATH)/quartus/bin/quartus_sh --determine_smart_action $(PROJECT) > smart.log

###################################################################
# Project initialization
###################################################################

$(ASSIGNMENT_FILES):
	$(QUARTUS_PATH)/quartus/bin/quartus_sh --prepare -f $(FAMILY) -t $(TOP_LEVEL_ENTITY) $(PROJECT)
	-cat $(BOARDFILE) >> $(PROJECT).qsf
map.chg:
	$(STAMP) map.chg
fit.chg:
	$(STAMP) fit.chg
sta.chg:
	$(STAMP) sta.chg
asm.chg:
	$(STAMP) asm.chg

###################################################################
# Programming the device
###################################################################

program: $(PROJECT).sof
	$(QUARTUS_PATH)/quartus/bin/quartus_pgm --mode=jtag -o "P;$(PROJECT).sof"
	
list:
	$(QUARTUS_PATH)/quartus/bin/quartus_pgm --list