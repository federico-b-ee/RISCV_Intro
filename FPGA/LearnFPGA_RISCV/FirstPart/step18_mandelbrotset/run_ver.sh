verilator -DTESTBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -Wno-fatal --top-module SOC -cc -exe testbench_verilator.cpp $1
cd obj_dir
make -f VSOC.mk
./VSOC