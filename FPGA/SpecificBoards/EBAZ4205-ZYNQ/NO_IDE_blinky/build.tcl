read_verilog "button.v"

# read constraints
read_xdc "EBAZ4205.xdc"

# synth
synth_design -top "SOC" -part "xc7z010clg400-1"

# place and route
opt_design
place_design
route_design

# write bitstream
write_bitstream -force "EBAZ4205_button.bit"
