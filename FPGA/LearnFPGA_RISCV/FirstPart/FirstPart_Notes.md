>- FOLLOWING: [Tutorial - Blinky to RISC-V](https://github.com/BrunoLevy/learn-fpga/blob/master/FemtoRV/TUTORIALS/FROM_BLINKER_TO_RISCV/README.md)

- [Cyclone IV - Useful Links](https://www.intel.com/content/www/us/en/docs/programmable/767845/current/cyclone-iv-featured-documentation-quick.html)

- [Video DE0nano](https://www.youtube.com/watch?v=UY7t2S7xUp4)

- [MIT Course](http://web.mit.edu/6.111/www/f2016/)

# iverilog

```sh
    sudo apt install iverilog
```

- [iverilog Flags](https://iverilog.fandom.com/wiki/Iverilog_Flags)

# RISCV

- [RISC-V Reference](https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/notebooks/RISCV/RISCV_CARD.pdf)

- [Volume I: RISC-V Unprivileged ISA(ref. page 130)](https://riscv.org/wp-content/uploads/2019/12/riscv-spec-20191213.pdf)

# Steps

## Step2 - ClockDivider

if i_clk = 50Mhz -> o_clk = i_clk / 2^DIV =(approx) 50Hz if DIV = 20.

Controlled Clock from Counter:

$f_{out} = f_{clk} \; \cfrac{\textbf{number to add}}{2^{\textbf{bits}}}$


## Step3 - LoadfromROM

To describe a ROM block: `reg [N-1:0] MEM [M-1:0]`

This means, the memory holds M values of N-bits -> it's an MxN memory block.

This block is usually synthesized and translated directly to BRAM. BRAM provides dedicated, on-chip memory blocks that can be used for storing data in digital circuits implemented on the FPGA.

To select a value of N-bits with an address: `MEM[A]` 

## Step7 - ALU and PC

We want the address of the current instruction. Since each instruction is 32-bits long, it means that:

- to increment PC, we do `PC <= PC + 4` (instead of `PC <= PC + 1` as before)
- to fetch the current instruction, we do `instr <= MEM[PC[31:2]];` (we ignore the two LSBs of PC).


## Error (10028): Can't resolve multiple constant drivers for net

```verilog
    // Datapath
    parameter FETCH = 0, REGS = 1, EXEC = 2;
    reg [1:0] state = FETCH;

    always @(posedge clk) begin
        case (state)
            FETCH: begin
                instr <= MEM[PC[31:2]];
                state <= REGS;
            end
            REGS: begin
                register_rs1 <= REGISTERBANK[rs1];
                register_rs2 <= REGISTERBANK[rs2];
                state <= EXEC;
            end
            EXEC: begin
                if (!instrtypes[System_Itype]) begin 
                    PC <= PC+4;
                end
                state <= FETCH;
            end
        endcase
        `ifdef TESTBENCH      
	        if(instrtypes[System_Itype]) $finish();
        `endif   
    end

    always @(posedge clk) begin
        `ifdef TESTBENCH	 
            if state $display("x%0d <= %b",rd,wrDATA);
        `endif	
        if(i_rst) begin
            PC    <= 0;
            state <= FETCH;
            instr <= 32'b0000000_00000_00000_000_00000_0110011; // noop
        end else begin
            if (wrEN && rd != 5'b00000) begin
                REGISTERBANK[rd] <= wrDATA;
            end
        end
    end
```

Solution:
```verilog
// Datapath
    parameter FETCH = 0, REGS = 1, EXEC = 2;
    reg [1:0] state = FETCH;

    always @(posedge clk) begin
        `ifdef TESTBENCH	 
            if state $display("x%0d <= %b",rd,wrDATA);
        `endif	

        if(i_rst) begin
            PC    <= 0;
            state <= FETCH;
            instr <= 32'b0000000_00000_00000_000_00000_0110011; // noop
        end else begin
            if (wrEN && rd != 5'b00000) begin
                REGISTERBANK[rd] <= wrDATA;
            end
        end

        case (state)
            FETCH: begin
                instr <= MEM[PC[31:2]];
                state <= REGS;
            end
            REGS: begin
                register_rs1 <= REGISTERBANK[rs1];
                register_rs2 <= REGISTERBANK[rs2];
                state <= EXEC;
            end
            EXEC: begin
                if (!instrtypes[System_Itype]) begin 
                    PC <= PC+4;
                end
                state <= FETCH;
            end
        endcase
        `ifdef TESTBENCH      
	        if(instrtypes[System_Itype]) $finish();
        `endif   
    end
```
The state machine and the reset should be in the same `always` statement.

## Step11 - RAM

The indexing doesn't take into account the first 2bits, since the memory's addresses have steps of 0x4 == 32bits. The first 2bits will always be equal to 0.
 
`o_rdata <= MEM[i_addr[31:2]];`

Synthetizing RAM with BRAM:

`reg[31:0] MEM [255:0];`

``` verilog
    initial begin
        // add x1, x0, x0
        //                    rs2   rs1  add  rd  ALUREG
        MEM[0] = 32'b0000000_00000_00000_000_00001_0110011;
        // addi x1, x1, 1
        //             imm         rs1  add  rd   ALUIMM
        MEM[1] = 32'b000000000001_00001_000_00001_0010011;
    end
```

### Using $readmemh()

test.s:
```asm
.global _start

_start:
    addi x1, x0, 1
    addi x1, x1, 1
    addi x1, x1, 1
```

Makefile:
```Makefile
PROGRAM := test
OUTPUT := output
all:
	riscv64-linux-gnu-as -march=rv32i -mabi=ilp32 $(PROGRAM).s -o $(PROGRAM).o
	riscv64-linux-gnu-objcopy -O binary $(PROGRAM).o $(PROGRAM).bin
	hexdump  -ve '1/4 "%08x\n"' $(PROGRAM).bin > $(PROGRAM).mem

clean: 
	rm -rf *.o *.bin *.mem
```

Inside the Vr_Memory.v module:

```verilog
    reg[31:0] MEM [255:0];
    // RAM

    initial begin 
        $readmemh("test.mem", MEM);
    end
```


## Step12 - Optimization

Why like this?

``` verilog
wire [31:0] nextPC = ((isBranch && takeBranch) || isJAL) ? PCplusImm  :	       
                    isJALR ? {aluPlus[31:1],1'b0}:
                    PCplus4;
```

Shouldn't it be `{aluPlus[31:2],2'b00}`, since the PC has steps of 4?

## Step13 - ASM -> Clock wait() function made in software.

- [RISCV-ASM-MANUAL](https://github.com/riscv-non-isa/riscv-asm-manual/blob/master/riscv-asm.md)

- [RISC-V Instruction Encoder/Decoder](https://luplab.gitlab.io/rvcodecjs/#q=ADD(x10,x0,x0)&abi=false&isa=AUTO)

- [RISC-V build 32-bit constants with LUI and ADDI](https://stackoverflow.com/questions/50742420/risc-v-build-32-bit-constants-with-lui-and-addi)


>- NOTE: identify enable and reset signals. Synthetizing usually initializes signals to zero but iverilog sets them to 'x', making the simulation work but the actual FPGA implementation doesn't.

```verilog
     if(!i_nrst) begin
```

## Step15 - Load instruction

```verilog
wire [31:0] loadstore_addr = rs1 + Iimm;
wire [15:0] LOAD_halfword = loadstore_addr[1] ? mem_rdata[31:16] : mem_rdata[15:0];
wire [7:0] LOAD_byte = loadstore_addr[0] ? LOAD_halfword[15:8] : LOAD_halfword[7:0];
```

```
The expressions loadstore_addr[1] and loadstore_addr[0] are being used to select specific portions of mem_rdata based on the lower bits of loadstore_addr.

Let's consider an example to illustrate this:

Assume rs1 contains the value 0x1000 and Iimm contains the value 4.

The calculation loadstore_addr = rs1 + Iimm would result in 0x1004.

Now, let's assume mem_rdata contains the value 0xAABBCCDD (32 bits).

In the line wire [15:0] LOAD_halfword = loadstore_addr[1] ? mem_rdata[31:16] : mem_rdata[15:0], the condition loadstore_addr[1] checks the second bit of loadstore_addr (bit at index 1). If this bit is 1, it means that the address is aligned to a half-word boundary (multiple of 2 bytes), and we select the upper 16 bits (mem_rdata[31:16]) of mem_rdata. Otherwise, if the second bit is 0, the address is not aligned to a half-word boundary, and we select the lower 16 bits (mem_rdata[15:0]) of mem_rdata.

In the line wire [7:0] LOAD_byte = loadstore_addr[0] ? LOAD_halfword[15:8] : LOAD_halfword[7:0], the condition loadstore_addr[0] checks the first bit of loadstore_addr (bit at index 0). If this bit is 1, it means that the address is aligned to a byte boundary (multiple of 1 byte), and we select the upper 8 bits (LOAD_halfword[15:8]) of LOAD_halfword. Otherwise, if the first bit is 0, the address is not aligned to a byte boundary, and we select the lower 8 bits (LOAD_halfword[7:0]) of LOAD_halfword.
```

So, the use of loadstore_addr[1] and loadstore_addr[0] as conditional checks allows selecting the appropriate portions of the data based on the alignment of the address and the desired load/store operation.

## Step16 - Store Instruction

Important:

```verilog
   assign mem_wdata[ 7: 0] = rs2[7:0];
   assign mem_wdata[15: 8] = loadstore_addr[0] ? rs2[7:0]  : rs2[15: 8];
   assign mem_wdata[23:16] = loadstore_addr[1] ? rs2[7:0]  : rs2[23:16];
   assign mem_wdata[31:24] = loadstore_addr[0] ? rs2[7:0]  :
			     loadstore_addr[1] ? rs2[15:8] : rs2[31:24];
```

## Step17 - Memory Mapping

> LI(sp,32'h1800);   // End of RAM, 6kB
> LI(gp,32'h400000); // IO page

one-hot decoding -> less hardware needed

```verilog
    localparam IO_LEDS_bit = 0;  
    reg [8:0] Hw_LEDS;
    always @(posedge clk) begin 
        //if the condition is true, the "virtual memory" is mapped to the LEDS
        if(isIO & IOEN & MEM_wordaddr[IO_LEDS_bit]) begin
            Hw_LEDS <= MEM_wdata[LEDS-1:0]; // The processor sends write data to a mem_addr. if the addr is above a threshold it's treated as a peripheral?
        end
    end
```

The virtual memory address for peripherals (VPaddr) is the 0x0040_0000. Each peripheral is "located" at the VPaddr + respective offset.

If 4 is added -> 0x0040_0004 -> note that the first 2 bits are not used, by left shifting 1-bit for every peripheral we have a VPaddr for 20 different peripherals encoded with the one-hot codification.

### Problems:

bne x10, x8, 20
1111 1110 0000 0010 1001 1110 1110 0011


################################################
Error con BRANCH:
1111 1110 0000 0011 0001 1100 1110 0011

bne x6, zero, 132 == bnez t1, 132
0000 1000 0000 0011 0001 0010 0110 0011

Debugging

                          1100011
1111111000000011000111001 1100011

***************************************
***************************************
PC=X <= PC_next=x
Immediate=4294967288
PC=X // PC_next=x // BRANCH // instr=11111110000000110001110011100011
***************************************
***************************************
################################################
> Problem with the LABEL
> Now there is another problem

Error w BRANCH or RET?
BRANCH:
0000010 00000 00110 001 01000 1100011

> The error was caused by ready_UART because of the clock divider.

BUG in BNEZ when asking for t1, the register has stored the 9th bit of the UART == the "ready_UART" bit.
It has some problems with low clocks

# Step18 & 19

it was `wire` alone

```verilog
    wire [3:0] STORE_MASK 
```

I wasn't using `$signed()` when computing right shifts with the ALU
```verilog
    3'h5: ALUoutput = (funct7[5]) ? ($signed(i_in1) >>> shamt) : ($signed(i_in1) >> shamt);  // srl
```

# Step19 - Verilator
Verilator is really useful, it runs faster and also prints errors and warnings.

# Step20 - Assembly
The linker (`.ld`) file and the steps described are almost mandatory. I did something similar, but the steps described are preferred.

Inside `Vr_Memory.v`:
```verilog
initial begin
    $readmemh("file.hex",MEM);
end
```

# Step22 - SPI Flash Memory and Optimizations

Only the optimizations were made. 
The SPI Flash Memory addition may vary from board to board.

```verilog
    assign o_rEN = ( state == FETCH_INSTR || (state == EXEC & instrtypes[Load_Itype]) );
    assign o_MEM_addr = (state == WAIT_INSTR || state == FETCH_INSTR) ? PC : loadstore_addr;
    assign o_wMASK = {4{ (state == EXEC) & instrtypes[Store_Stype] }} & STORE_MASK;

    // Datapath
    parameter FETCH_INSTR = 0, EXEC = 1, WAIT_INSTR = 2, WAIT_DATA = 3;
    reg [1:0] state = FETCH_INSTR;

    always @(posedge i_clk) begin

        if(!i_nrst) begin
            PC    <= 0;
            state <= FETCH_INSTR;
            instr <= 32'b0000000_00000_00000_000_00000_0110011; // noop
        end else begin
            if (wrEN && rd != 5'b00000) begin
                REGISTERBANK[rd] <= wrDATA;
            end
        end

        case (state)
            FETCH_INSTR: begin
                state <= WAIT_INSTR;
            end
            WAIT_INSTR: begin
                instr <= i_MEM_rdata;
                register_rs1 <= REGISTERBANK[i_MEM_rdata[19:15]];//i_MEM_rdata[19:15] == rs1
                register_rs2 <= REGISTERBANK[i_MEM_rdata[24:20]];//i_MEM_rdata[24:20] == rs2
                state <= EXEC;
            end
            EXEC: begin
                if (!instrtypes[System_Itype]) begin 
                    PC <= PCnext;
                end
                state <= instrtypes[Load_Itype] ? WAIT_DATA : FETCH_INSTR;
            end
            WAIT_DATA: begin
                state <= FETCH_INSTR;
            end
            default: begin
                state <= FETCH_INSTR;
            end
        endcase
        `ifdef TESTBENCH      
	        if(instrtypes[System_Itype]) $finish();
        `endif   
    end
```
From 6 states to 4, reducing the CPI(Clocks Per Instruction).

> The PC, PC_next and all address related `wires/signals` are 32-bits, they can use fewer bits.

> The first 2-bits of any RV32I instruction is always `2'b11`. We can load the instruction to the instruction register as follows: 
```verilog
reg [31:2] instr;
instr <= i_MEM_rdata[32:2];
```
