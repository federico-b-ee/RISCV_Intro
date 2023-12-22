verilator -DTESTBENCH -DBOARD_FREQ=50 -DCPU_FREQ=50 -Wno-fatal --top-module SOC -cc -exe testbench_verilator.cpp $1
cd obj_dir
cp ../DATARAM.mem .
cp ../PROGROM.mem .
make -f VSOC.mk
./VSOC