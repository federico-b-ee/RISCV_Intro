# nextpnr
cmake . -DARCH=gowin -DBUILD_GUI=ON
make -j$(nproc)
sudo make install

# Gowin Tangnano9k toolchain 

- yosys -> synthesis
- nextpnr -> place and route
- apicula -> bitstream 
- openFPGALoader -> flash
