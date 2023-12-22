read_verilog "step15.v"

# read constraints
read_xdc "zybo.xdc"

# synth
synth_design -top "SOC" -part "xc7z010clg400-1"

# place and route
opt_design
place_design
route_design

# write bitstream
write_bitstream -force "ZYBO_RISCV.bit"