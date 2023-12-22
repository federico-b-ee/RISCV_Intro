`include "Vr_RV32I_ISA.v"
`include "Vr_ALU.v"

module Vr_RV32I_Processor (
    input i_clk,
    input i_nrst,
    input [31:0] i_IO_MEM_rdata,
    output [31:0] o_IO_MEM_addr,
    output o_IO_MEM_wr,
    output [31:0] o_IO_MEM_wdata

);
  // Memory

  assign o_IO_MEM_wr = isIO & wMASK[0];
  assign o_IO_MEM_addr = MEM_addr;
  assign o_IO_MEM_wdata = MEM_wdata;
  assign MEM_rdata = isRAM ? DATARAM_rdata : i_IO_MEM_rdata;
  //reg [31:0] PROGROM[0:3839];  // 3840 * 32 / (8*1024) = 15kB // LENGTH = 0x3C00
  //reg [31:0] DATARAM[0:3839];  // 3840 * 32 / (8*1024) = 15kB // LENGTH = 0x3C00
  reg [31:0] PROGROM[0:16383];
  reg [31:0] DATARAM[0:16383];
  initial begin
    $readmemh("PROGROM.hex", PROGROM);  // Instructions         -> RX (Read Only)
    $readmemh("DATARAM.hex", DATARAM);  // Load and Store DATA  -> RW (Read/Write)
  end

  wire [31:0] MEM_wdata;
  wire [31:0] MEM_rdata;
  wire [31:0] MEM_addr;
  wire [3:0] wMASK;

  wire isIO = MEM_addr[22];
  wire isRAM = !isIO;

  //wire [11:0] MEM_word_addr = MEM_addr[13:2]; // Up to 0x3FFF, we need 0x3C00 max
  wire [13:0] MEM_word_addr = MEM_addr[15:2];
  reg [31:0] DATARAM_rdata;
  wire [3:0] DATARAM_wmask = wMASK & {4{isRAM}};

  always @(posedge i_clk) begin
    DATARAM_rdata <= DATARAM[MEM_word_addr];
    if (DATARAM_wmask[0]) DATARAM[MEM_word_addr][7:0] <= MEM_wdata[7:0];
    if (DATARAM_wmask[1]) DATARAM[MEM_word_addr][15:8] <= MEM_wdata[15:8];
    if (DATARAM_wmask[2]) DATARAM[MEM_word_addr][23:16] <= MEM_wdata[23:16];
    if (DATARAM_wmask[3]) DATARAM[MEM_word_addr][31:24] <= MEM_wdata[31:24];
  end

  // Register Bank
  reg  [31:0] PC = 0;
  reg  [31:0] instr;

  reg  [31:0] REGISTERBANK [31:0];
  reg  [31:0] register_rs1;
  reg  [31:0] register_rs2;
  reg  [31:0] register_rd;

  // RV32I ISA
  wire [ 9:0] instrtypes;
  wire [4:0] rs1, rs2, rd;
  wire [31:0] imm;
  wire [ 2:0] funct3;
  wire [ 6:0] funct7;

  parameter ALU_Rtype = 0;
  parameter ALU_Itype = 1;
  parameter Load_Itype = 2;
  parameter Store_Stype = 3;
  parameter Branch_Btype = 4;
  parameter JAL_Jtype = 5;
  parameter JALR_Itype = 6;
  parameter LUI_Utype = 7;
  parameter AUIPC_Utype = 8;
  parameter System_Itype = 9;

  Vr_RV32I_ISA RV32I_ISA (
      .i_instr(instr),
      .o_instrtypes(instrtypes),
      .o_rs1(rs1),
      .o_rs2(rs2),
      .o_rd(rd),
      .o_imm(imm),
      .o_funct3(funct3),
      .o_funct7(funct7)
  );

  // ALU - The shifter can be optimized more too

  wire [31:0] PC_plus_imm = PC + imm;

  wire [31:0] PC_plus_4 = PC + 4;

  wire [31:0] ALU_in2 = (instrtypes[ALU_Rtype] | instrtypes[Branch_Btype]) ? register_rs2 : imm;

  wire [31:0] ALUoutput;
  wire [31:0] wrDATA = (instrtypes[JAL_Jtype] || instrtypes[JALR_Itype])
       ? PC_plus_4
       : instrtypes[LUI_Utype]
       ? imm
       : instrtypes[AUIPC_Utype]
       ? PC_plus_imm
       : instrtypes[Load_Itype]
       ? ldDATA
       : ALUoutput;

  wire wrEN = (state == EXEC &&
               !instrtypes[Load_Itype] &&
               !instrtypes[Store_Stype] &&
               !instrtypes[Branch_Btype]) || (state == WAIT_DATA);

  Vr_ALU ALU (
      .i_in1(register_rs1),
      .i_in2(ALU_in2),
      .i_instr(instr),
      .o_out(ALUoutput),
      .o_ALUadd(ALUadd),
      .o_EQ(EQ),
      .o_LT(LT),
      .o_LTU(LTU)
  );

  //
  wire [31:0] ALUadd;
  wire EQ, LT, LTU;

  // Branch Handler -> The ALU can be used to decrease the LUTs needed.

  reg takeBranch;
  always @(*) begin
    case (funct3)
      3'b000:  takeBranch = EQ;
      3'b001:  takeBranch = !EQ;
      3'b100:  takeBranch = LT;
      3'b101:  takeBranch = !LT;
      3'b110:  takeBranch = LTU;
      3'b111:  takeBranch = !LTU;
      default: takeBranch = 1'b0;
    endcase
  end

  wire [31:0] PCnext = ((instrtypes[Branch_Btype] && takeBranch) || instrtypes[JAL_Jtype])
       ? PC_plus_imm
       : (instrtypes[JALR_Itype]
          ? {ALUadd[31:1], 1'b0}
          : PC_plus_4);

  // Load and Store Handler

  // LOAD
  wire [31:0] loadstore_addr = register_rs1 + imm; // the implementation detects that the imm = imm_Itype or imm_Stype
  wire [15:0] LOAD_h = loadstore_addr[1] ? MEM_rdata[31:16] : MEM_rdata[15:0];
  wire [7:0] LOAD_b = loadstore_addr[0] ? LOAD_h[15:8] : LOAD_h[7:0];

  wire EN_byte = (funct3[1:0] == 2'b00);
  wire EN_hw = (funct3[1:0] == 2'b01);

  wire LOAD_sign = !funct3[1] & (EN_byte ? LOAD_b[7] : LOAD_h[15]);  //!funct3[1] -> not load word

  wire [31:0] ldDATA =    EN_byte ? {{24{LOAD_sign}}, LOAD_b} :
       EN_hw ? {{16{LOAD_sign}}, LOAD_h} :
       MEM_rdata;

  // STORE
  assign MEM_wdata[7:0] = register_rs2[7:0];

  assign MEM_wdata[15:8] = loadstore_addr[0] ? register_rs2[7:0] : register_rs2[15:8];

  assign MEM_wdata[23:16] = loadstore_addr[1] ? register_rs2[7:0] : register_rs2[23:16];

  assign MEM_wdata[31:24] = loadstore_addr[0] ? register_rs2[7:0] :
         loadstore_addr[1] ? register_rs2[15:8] : register_rs2[31:24];


  wire [3:0] STORE_MASK =
       EN_byte     ?
       (loadstore_addr[1] ?
        (loadstore_addr[0] ? 4'b1000 : 4'b0100) :
        (loadstore_addr[0] ? 4'b0010 : 4'b0001)
       ) :
       EN_hw       ?
       (loadstore_addr[1] ? 4'b1100 : 4'b0011) :
       4'b1111;


  assign MEM_addr = loadstore_addr;
  assign wMASK = {4{(state == EXEC) & instrtypes[Store_Stype]}} & STORE_MASK;

  // Datapath
  parameter FETCH_INSTR = 0, EXEC = 1, WAIT_INSTR = 2, WAIT_DATA = 3;
  reg [1:0] state = FETCH_INSTR;

  always @(posedge i_clk) begin

    if (!i_nrst) begin
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
        //instr <= PROGROM[PC[13:2]];
        instr <= PROGROM[PC[15:2]];
      end
      WAIT_INSTR: begin
        register_rs1 <= REGISTERBANK[instr[19:15]];  //MEM_rdata[19:15] == rs1
        register_rs2 <= REGISTERBANK[instr[24:20]];  //MEM_rdata[24:20] == rs2
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

    //if (instrtypes[System_Itype]) $finish();
`endif

  end

  // Testbench

`ifdef TESTBENCH
  integer i;
  initial begin
    for (i = 0; i < 32; ++i) begin
      REGISTERBANK[i] = 0;
    end
  end
  always @(posedge i_clk) begin
    if (0) begin
      $display("***************************************");
      $display("PC=%0d <= PC_next=%0d", PC, PCnext);
      $display("Immediate=%0d == %b", imm, imm);
      $display("Instr:%b", instr);
      $display("takeBranch:%b || funct3:%b", takeBranch, funct3);
      $display("ALU_in2:%0d == %b", ALU_in2, ALU_in2);
      $display("rs1:%0d == %b", register_rs1, register_rs1);
      case (1'b1)
        instrtypes[ALU_Rtype]:
        $display(
            "PC=%0d // ALUreg rd=%d rs1=%d rs2=%d funct3=%b instr=%b",
            PC,
            rd,
            rs1,
            rs2,
            funct3,
            instr
        );
        instrtypes[ALU_Itype]:
        $display(
            "PC=%0d // ALUimm rd=%d rs1=%d rs2=%d funct3=%b state=%d",
            PC,
            rd,
            rs1,
            rs2,
            funct3,
            state
        );
        instrtypes[Load_Itype]: $display("PC=%0d // Load", PC);
        instrtypes[Store_Stype]: $display("PC=%0d // Store", PC);
        instrtypes[Branch_Btype]:
        $display("PC=%0d // PC_next=%0d // BRANCH // instr=%b", PC, PCnext, instr);
        instrtypes[JAL_Jtype]: $display("PC=%0d // JAL", PC);
        instrtypes[JALR_Itype]: $display("PC=%0d // JALR", PC);
        instrtypes[LUI_Utype]: $display("PC=%0d // LUI", PC);
        instrtypes[AUIPC_Utype]: $display("PC=%0d // AUIPC", PC);
        instrtypes[System_Itype]: $display("PC=%0d // SYSTEM", PC);
      endcase
      $display("***************************************");
    end
  end
`endif
endmodule
