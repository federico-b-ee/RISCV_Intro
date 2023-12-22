# DE0nano Demo

![Demo](demo.gif)

# RV32I / FemtoRV core 
This is an implementation following Bruno Levy's repository/tutorial.

The dir `/RV32I_ASM_step15` has a Makefile that produces a `.mem` file. Is used to initialize the memory as follows:

inside Vr_Memory.v
```verilog
    initial begin
        $readmemh("test.mem", MEM);
    end
```

Because the linker script and the size of the memory is not defined and depends on the BRAM of each chip, the way to "store" data in memory is the following:

```verilog
    initial begin
        $readmemh("test.mem", MEM); 
        MEM[100] = {8'h4, 8'h3, 8'h2, 8'h1};
    end
```
With `MEM[100]` we are storing a 32-bit variable inside the MEM address = 100.

# The ASM Program

The ASM program fetches the data stored in memory into `a0 == x10` &rarr; [ABI name of Registers](https://en.wikichip.org/wiki/risc-v/registers)

And the LEDS of the board are wired directly to `x10`, the count of 0 up to 15 should be displayed in binary.

# How to Flash the Verilog code to the Zybo?

1. First of all, the Vivado's setup script has to be run:

```sh
    . /Xilinx/Vivado/2023.1/settings64.sh  
```
> Don't forget to check the path and version.

2. Now the `.tcl` file, it's not the same as Intel's 

I followed this [tutorial](https://projectf.io/posts/vivado-tcl-build-script/) and adapted what is explained to the zybo and our filesystem:

```sh
read_verilog "step15.v"

# read constraints
read_xdc "zybo.xdc"

# synth
synth_design -top "SOC" -part "xc7z010clg400c-1"

# place and route
opt_design
place_design
route_design

# write bitstream
write_bitstream -force "ZYBO_RISCV.bit"
```
> [.xdc Digilent's Reference](https://digilent.com/reference/programmable-logic/guides/vivado-xdc-file)

3. Finally, we create the bitsream:

```sh
    vivado -mode batch -nolog -nojournal -source build.tcl 
```

And the bitstream is called `"ZYBO_RISCV.bit"`

> Using the Makefile &rarr; `make` 

# Flashing the bitstream

openFPGALoader is proposed in the [tutorial](https://projectf.io/posts/vivado-tcl-build-script/), it's a great tool. It can be used with many boards and with a simple command.

- [Repository](https://github.com/trabucayre/openFPGALoader)
- [Installation](https://trabucayre.github.io/openFPGALoader/guide/install.html)
- [Supported Boards](https://trabucayre.github.io/openFPGALoader/compatibility/board.html)  

The command used for the Zybo is:
```sh
    openFPGALoader -b zybo_z7_10 ZYBO_RISCV.bit
```

> Using the Makefile &rarr; `make fpgaload` 