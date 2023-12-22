// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VSOC_H_
#define _VSOC_H_  // guard

#include "verilated_heavy.h"

//==========

class VSOC__Syms;

//----------

VL_MODULE(VSOC) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(i_clk,0,0);
    VL_IN8(i_rst,0,0);
    VL_OUT8(o_leds,2,0);
    VL_IN8(RXD,0,0);
    VL_OUT8(TXD,0,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*2:0*/ SOC__DOT__Hw_LEDS;
    CData/*3:0*/ SOC__DOT__Processor__DOT__wMASK;
    CData/*3:0*/ SOC__DOT__Processor__DOT__DATARAM_wmask;
    CData/*0:0*/ SOC__DOT__Processor__DOT__takeBranch;
    CData/*7:0*/ SOC__DOT__Processor__DOT__LOAD_b;
    CData/*0:0*/ SOC__DOT__Processor__DOT__LOAD_sign;
    CData/*1:0*/ SOC__DOT__Processor__DOT__state;
    CData/*4:0*/ SOC__DOT__Processor__DOT__ALU__DOT__shamt;
    CData/*0:0*/ SOC__DOT__Processor__DOT__ALU__DOT__LT;
    SData/*9:0*/ SOC__DOT__Processor__DOT__instrtypes;
    SData/*15:0*/ SOC__DOT__Processor__DOT__LOAD_h;
    IData/*31:0*/ SOC__DOT__IO_MEM_rdata;
    IData/*31:0*/ SOC__DOT__Processor__DOT__MEM_wdata;
    IData/*31:0*/ SOC__DOT__Processor__DOT__MEM_rdata;
    IData/*31:0*/ SOC__DOT__Processor__DOT__DATARAM_rdata;
    IData/*31:0*/ SOC__DOT__Processor__DOT__PC;
    IData/*31:0*/ SOC__DOT__Processor__DOT__instr;
    IData/*31:0*/ SOC__DOT__Processor__DOT__register_rs1;
    IData/*31:0*/ SOC__DOT__Processor__DOT__register_rs2;
    IData/*31:0*/ SOC__DOT__Processor__DOT__imm;
    IData/*31:0*/ SOC__DOT__Processor__DOT__PC_plus_imm;
    IData/*31:0*/ SOC__DOT__Processor__DOT__ALU_in2;
    IData/*31:0*/ SOC__DOT__Processor__DOT__PCnext;
    IData/*31:0*/ SOC__DOT__Processor__DOT__loadstore_addr;
    IData/*31:0*/ SOC__DOT__Processor__DOT__ALU__DOT__ALUadd;
    QData/*32:0*/ SOC__DOT__Processor__DOT__ALU__DOT__ALUsub;
    IData/*31:0*/ SOC__DOT__Processor__DOT__PROGROM[16384];
    IData/*31:0*/ SOC__DOT__Processor__DOT__DATARAM[16384];
    IData/*31:0*/ SOC__DOT__Processor__DOT__REGISTERBANK[32];
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*5:0*/ __Vtableidx1;
    CData/*0:0*/ __Vclklast__TOP__i_clk;
    static CData/*0:0*/ __Vtable1_SOC__DOT__Processor__DOT__takeBranch[64];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    VSOC__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(VSOC);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    VSOC(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~VSOC();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(VSOC__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(VSOC__Syms* symsp, bool first);
  private:
    static QData _change_request(VSOC__Syms* __restrict vlSymsp);
    static QData _change_request_1(VSOC__Syms* __restrict vlSymsp);
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(VSOC__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(VSOC__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(VSOC__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__3(VSOC__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__1(VSOC__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(VSOC__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__4(VSOC__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
