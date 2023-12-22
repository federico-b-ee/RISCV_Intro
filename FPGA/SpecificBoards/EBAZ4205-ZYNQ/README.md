## RISCV on ZYNQ

The RISCV Processor has been synthetized to run on a ZYNQ. 

The ILA IP Block from Xilinx was used to test some functionalities. The BlockDiagram shows the wiring.

![Board's img](EBAZ4205.jpg)

## Install Cable Drivers (JTAG programmer)


```sh
cd /tools/Xilinx/Vivado/2023.1/data/xicom/cable_drivers/lin64/install_script/install_drivers
sudo ./install_drivers 
```

* [RISCV DECODER](https://luplab.gitlab.io/rvcodecjs/#q=fff28293&abi=true&isa=RV32I)

## Links

* [GitHub - xjtuecho/EBAZ4205: A 5$ Xilinx ZYNQ development board.](https://github.com/xjtuecho/EBAZ4205)
* [EBAZ4205/HW/ebaz4205/EBAZ4205-SCH.pdf at master · xjtuecho/EBAZ4205 · GitHub](https://github.com/xjtuecho/EBAZ4205/blob/master/HW/ebaz4205/EBAZ4205-SCH.pdf)
* [Styx: How to use Xilinx Zynq PS PLL Clocks in FPGA Fabric | Numato Lab Help Center](https://numato.com/kb/styx-use-xilinx-zynq-ps-pll-clocks-fpga-fabric/)
* [samplecode/FPGA/numatoVivadoBSP/styx/1.0/board.xml at master · numato/samplecode · GitHub](https://github.com/numato/samplecode/blob/master/FPGA/numatoVivadoBSP/styx/1.0/board.xml)
* [Creating Xilinx Vivado board files for EBAZ4205 - Hackster.io](https://www.hackster.io/mindaugas2/creating-xilinx-vivado-board-files-for-ebaz4205-a7b120)
* [ZYNQ for beginners: programming and connecting the PS and PL | Part 2 - YouTube](https://www.youtube.com/watch?v=AOy5l36DroY)
* [Install Cable Drivers (Linux Only) - Digilent Reference](https://digilent.com/reference/programmable-logic/guides/install-cable-drivers)

- [Playlist AXI](https://youtube.com/playlist?list=PL9K1-gZiaFsN-OLaN7mxfhWC4iFF82X6I&feature=shared)
- [Playlist ZYNQ](https://www.youtube.com/playlist?list=PL4D6H9w4Ihdp0YRExoQXfbVMRL1GgEPCm)
- [AXI XADC ES](https://www.youtube.com/watch?v=CweKlwsXUY0)
- [AXI XADC 2 ES](https://www.youtube.com/watch?v=s9VygjbWtjk)