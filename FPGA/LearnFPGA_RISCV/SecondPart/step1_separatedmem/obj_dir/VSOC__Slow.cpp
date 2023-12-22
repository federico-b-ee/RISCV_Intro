// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSOC.h for the primary calling header

#include "VSOC.h"
#include "VSOC__Syms.h"

//==========
CData/*0:0*/ VSOC::__Vtable1_SOC__DOT__Processor__DOT__takeBranch[64];

VL_CTOR_IMP(VSOC) {
    VSOC__Syms* __restrict vlSymsp = __VlSymsp = new VSOC__Syms(this, name());
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void VSOC::__Vconfigure(VSOC__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

VSOC::~VSOC() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void VSOC::_settle__TOP__2(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_settle__TOP__2\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_leds = vlTOPp->SOC__DOT__Hw_LEDS;
    vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata = (
                                                   (0xffffff00U 
                                                    & vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata) 
                                                   | (0xffU 
                                                      & vlTOPp->SOC__DOT__Processor__DOT__register_rs2));
    vlTOPp->SOC__DOT__Processor__DOT__instrtypes = 
        (((0x73U == (0x7fU & vlTOPp->SOC__DOT__Processor__DOT__instr)) 
          << 9U) | (((0x17U == (0x7fU & vlTOPp->SOC__DOT__Processor__DOT__instr)) 
                     << 8U) | (((0x37U == (0x7fU & vlTOPp->SOC__DOT__Processor__DOT__instr)) 
                                << 7U) | (((0x67U == 
                                            (0x7fU 
                                             & vlTOPp->SOC__DOT__Processor__DOT__instr)) 
                                           << 6U) | 
                                          (((0x6fU 
                                             == (0x7fU 
                                                 & vlTOPp->SOC__DOT__Processor__DOT__instr)) 
                                            << 5U) 
                                           | (((0x63U 
                                                == 
                                                (0x7fU 
                                                 & vlTOPp->SOC__DOT__Processor__DOT__instr)) 
                                               << 4U) 
                                              | (((0x23U 
                                                   == 
                                                   (0x7fU 
                                                    & vlTOPp->SOC__DOT__Processor__DOT__instr)) 
                                                  << 3U) 
                                                 | (((3U 
                                                      == 
                                                      (0x7fU 
                                                       & vlTOPp->SOC__DOT__Processor__DOT__instr)) 
                                                     << 2U) 
                                                    | (((0x13U 
                                                         == 
                                                         (0x7fU 
                                                          & vlTOPp->SOC__DOT__Processor__DOT__instr)) 
                                                        << 1U) 
                                                       | (0x33U 
                                                          == 
                                                          (0x7fU 
                                                           & vlTOPp->SOC__DOT__Processor__DOT__instr)))))))))));
    vlTOPp->SOC__DOT__Processor__DOT__imm = (((((0x13U 
                                                 == 
                                                 (0x7fU 
                                                  & vlTOPp->SOC__DOT__Processor__DOT__instr)) 
                                                | (3U 
                                                   == 
                                                   (0x7fU 
                                                    & vlTOPp->SOC__DOT__Processor__DOT__instr))) 
                                               | (0x67U 
                                                  == 
                                                  (0x7fU 
                                                   & vlTOPp->SOC__DOT__Processor__DOT__instr))) 
                                              | (0x73U 
                                                 == 
                                                 (0x7fU 
                                                  & vlTOPp->SOC__DOT__Processor__DOT__instr)))
                                              ? ((0xfffff800U 
                                                  & ((- (IData)(
                                                                (1U 
                                                                 & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                                    >> 0x1fU)))) 
                                                     << 0xbU)) 
                                                 | (0x7ffU 
                                                    & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                       >> 0x14U)))
                                              : ((0x23U 
                                                  == 
                                                  (0x7fU 
                                                   & vlTOPp->SOC__DOT__Processor__DOT__instr))
                                                  ? 
                                                 ((0xfffff800U 
                                                   & ((- (IData)(
                                                                 (1U 
                                                                  & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                                     >> 0x1fU)))) 
                                                      << 0xbU)) 
                                                  | ((0x7e0U 
                                                      & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                         >> 0x14U)) 
                                                     | (0x1fU 
                                                        & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                           >> 7U))))
                                                  : 
                                                 ((0x63U 
                                                   == 
                                                   (0x7fU 
                                                    & vlTOPp->SOC__DOT__Processor__DOT__instr))
                                                   ? 
                                                  ((0xfffff000U 
                                                    & ((- (IData)(
                                                                  (1U 
                                                                   & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                                      >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | ((0x800U 
                                                       & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                          << 4U)) 
                                                      | ((0x7e0U 
                                                          & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                             >> 0x14U)) 
                                                         | (0x1eU 
                                                            & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                               >> 7U)))))
                                                   : 
                                                  ((0x6fU 
                                                    == 
                                                    (0x7fU 
                                                     & vlTOPp->SOC__DOT__Processor__DOT__instr))
                                                    ? 
                                                   ((0xfff00000U 
                                                     & ((- (IData)(
                                                                   (1U 
                                                                    & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                                       >> 0x1fU)))) 
                                                        << 0x14U)) 
                                                    | ((0xff000U 
                                                        & vlTOPp->SOC__DOT__Processor__DOT__instr) 
                                                       | ((0x800U 
                                                           & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                              >> 9U)) 
                                                          | (0x7feU 
                                                             & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                                >> 0x14U)))))
                                                    : 
                                                   (((0x17U 
                                                      == 
                                                      (0x7fU 
                                                       & vlTOPp->SOC__DOT__Processor__DOT__instr)) 
                                                     | (0x37U 
                                                        == 
                                                        (0x7fU 
                                                         & vlTOPp->SOC__DOT__Processor__DOT__instr)))
                                                     ? 
                                                    (0xfffff000U 
                                                     & vlTOPp->SOC__DOT__Processor__DOT__instr)
                                                     : 0U)))));
    vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr 
        = (vlTOPp->SOC__DOT__Processor__DOT__register_rs1 
           + vlTOPp->SOC__DOT__Processor__DOT__imm);
    vlTOPp->SOC__DOT__Processor__DOT__ALU_in2 = ((1U 
                                                  & ((IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes) 
                                                     | ((IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes) 
                                                        >> 4U)))
                                                  ? vlTOPp->SOC__DOT__Processor__DOT__register_rs2
                                                  : vlTOPp->SOC__DOT__Processor__DOT__imm);
    vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata = (
                                                   (0xffff00ffU 
                                                    & vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata) 
                                                   | (0xff00U 
                                                      & (((1U 
                                                           & vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr)
                                                           ? vlTOPp->SOC__DOT__Processor__DOT__register_rs2
                                                           : 
                                                          (vlTOPp->SOC__DOT__Processor__DOT__register_rs2 
                                                           >> 8U)) 
                                                         << 8U)));
    vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata = (
                                                   (0xff00ffffU 
                                                    & vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata) 
                                                   | (0xff0000U 
                                                      & (((2U 
                                                           & vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr)
                                                           ? vlTOPp->SOC__DOT__Processor__DOT__register_rs2
                                                           : 
                                                          (vlTOPp->SOC__DOT__Processor__DOT__register_rs2 
                                                           >> 0x10U)) 
                                                         << 0x10U)));
    vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata = (
                                                   (0xffffffU 
                                                    & vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata) 
                                                   | (0xff000000U 
                                                      & (((1U 
                                                           & vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr)
                                                           ? vlTOPp->SOC__DOT__Processor__DOT__register_rs2
                                                           : 
                                                          ((2U 
                                                            & vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr)
                                                            ? 
                                                           (vlTOPp->SOC__DOT__Processor__DOT__register_rs2 
                                                            >> 8U)
                                                            : 
                                                           (vlTOPp->SOC__DOT__Processor__DOT__register_rs2 
                                                            >> 0x18U))) 
                                                         << 0x18U)));
    vlTOPp->SOC__DOT__Processor__DOT__MEM_rdata = (
                                                   (0x400000U 
                                                    & vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr)
                                                    ? vlTOPp->SOC__DOT__IO_MEM_rdata
                                                    : vlTOPp->SOC__DOT__Processor__DOT__DATARAM_rdata);
    vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__shamt 
        = (0x1fU & ((0x20U & vlTOPp->SOC__DOT__Processor__DOT__instr)
                     ? vlTOPp->SOC__DOT__Processor__DOT__ALU_in2
                     : (vlTOPp->SOC__DOT__Processor__DOT__instr 
                        >> 0x14U)));
    vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__ALUadd 
        = (vlTOPp->SOC__DOT__Processor__DOT__register_rs1 
           + vlTOPp->SOC__DOT__Processor__DOT__ALU_in2);
    vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__ALUsub 
        = (0x1ffffffffULL & (1ULL + ((QData)((IData)(vlTOPp->SOC__DOT__Processor__DOT__register_rs1)) 
                                     + (0x100000000ULL 
                                        | (QData)((IData)(
                                                          (~ vlTOPp->SOC__DOT__Processor__DOT__ALU_in2)))))));
    vlTOPp->SOC__DOT__Processor__DOT__LOAD_h = (0xffffU 
                                                & ((2U 
                                                    & vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr)
                                                    ? 
                                                   (vlTOPp->SOC__DOT__Processor__DOT__MEM_rdata 
                                                    >> 0x10U)
                                                    : vlTOPp->SOC__DOT__Processor__DOT__MEM_rdata));
    vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__LT 
        = (1U & ((0x80000000U & (vlTOPp->SOC__DOT__Processor__DOT__register_rs1 
                                 ^ vlTOPp->SOC__DOT__Processor__DOT__ALU_in2))
                  ? (vlTOPp->SOC__DOT__Processor__DOT__register_rs1 
                     >> 0x1fU) : (IData)((vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__ALUsub 
                                          >> 0x20U))));
    vlTOPp->SOC__DOT__Processor__DOT__LOAD_b = (0xffU 
                                                & ((1U 
                                                    & vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr)
                                                    ? 
                                                   ((IData)(vlTOPp->SOC__DOT__Processor__DOT__LOAD_h) 
                                                    >> 8U)
                                                    : (IData)(vlTOPp->SOC__DOT__Processor__DOT__LOAD_h)));
    vlTOPp->__Vtableidx1 = (((0U == (IData)(vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__ALUsub)) 
                             << 5U) | (((IData)(vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__LT) 
                                        << 4U) | ((8U 
                                                   & ((IData)(
                                                              (vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__ALUsub 
                                                               >> 0x20U)) 
                                                      << 3U)) 
                                                  | (7U 
                                                     & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                        >> 0xcU)))));
    vlTOPp->SOC__DOT__Processor__DOT__takeBranch = 
        vlTOPp->__Vtable1_SOC__DOT__Processor__DOT__takeBranch
        [vlTOPp->__Vtableidx1];
    vlTOPp->SOC__DOT__Processor__DOT__LOAD_sign = (1U 
                                                   & ((~ 
                                                       (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                        >> 0xdU)) 
                                                      & ((0U 
                                                          == 
                                                          (3U 
                                                           & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                              >> 0xcU)))
                                                          ? 
                                                         ((IData)(vlTOPp->SOC__DOT__Processor__DOT__LOAD_b) 
                                                          >> 7U)
                                                          : 
                                                         ((IData)(vlTOPp->SOC__DOT__Processor__DOT__LOAD_h) 
                                                          >> 0xfU))));
}

void VSOC::_initial__TOP__3(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_initial__TOP__3\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp1[3];
    WData/*95:0*/ __Vtemp2[3];
    // Body
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[1U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[2U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[3U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[4U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[5U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[6U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[7U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[8U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[9U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0xaU] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0xbU] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0xcU] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0xdU] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0xeU] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0xfU] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x10U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x11U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x12U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x13U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x14U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x15U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x16U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x17U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x18U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x19U] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x1aU] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x1bU] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x1cU] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x1dU] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x1eU] = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[0x1fU] = 0U;
    __Vtemp1[0U] = 0x2e686578U;
    __Vtemp1[1U] = 0x47524f4dU;
    __Vtemp1[2U] = 0x50524fU;
    VL_READMEM_N(true, 32, 16384, 0, VL_CVT_PACK_STR_NW(3, __Vtemp1)
                 , vlTOPp->SOC__DOT__Processor__DOT__PROGROM
                 , 0, ~0ULL);
    __Vtemp2[0U] = 0x2e686578U;
    __Vtemp2[1U] = 0x4152414dU;
    __Vtemp2[2U] = 0x444154U;
    VL_READMEM_N(true, 32, 16384, 0, VL_CVT_PACK_STR_NW(3, __Vtemp2)
                 , vlTOPp->SOC__DOT__Processor__DOT__DATARAM
                 , 0, ~0ULL);
    vlTOPp->SOC__DOT__Processor__DOT__state = 0U;
    vlTOPp->SOC__DOT__Processor__DOT__PC = 0U;
}

void VSOC::_settle__TOP__4(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_settle__TOP__4\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->SOC__DOT__Processor__DOT__wMASK = ((- (IData)(
                                                          ((1U 
                                                            == (IData)(vlTOPp->SOC__DOT__Processor__DOT__state)) 
                                                           & ((IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes) 
                                                              >> 3U)))) 
                                               & ((0U 
                                                   == 
                                                   (3U 
                                                    & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                       >> 0xcU)))
                                                   ? 
                                                  ((2U 
                                                    & vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr)
                                                    ? 
                                                   ((1U 
                                                     & vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr)
                                                     ? 8U
                                                     : 4U)
                                                    : 
                                                   ((1U 
                                                     & vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr)
                                                     ? 2U
                                                     : 1U))
                                                   : 
                                                  ((1U 
                                                    == 
                                                    (3U 
                                                     & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                        >> 0xcU)))
                                                    ? 
                                                   ((2U 
                                                     & vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr)
                                                     ? 0xcU
                                                     : 3U)
                                                    : 0xfU)));
    vlTOPp->SOC__DOT__Processor__DOT__PC_plus_imm = 
        (vlTOPp->SOC__DOT__Processor__DOT__PC + vlTOPp->SOC__DOT__Processor__DOT__imm);
    vlTOPp->SOC__DOT__Processor__DOT__DATARAM_wmask 
        = ((IData)(vlTOPp->SOC__DOT__Processor__DOT__wMASK) 
           & (- (IData)((1U & (~ (vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr 
                                  >> 0x16U))))));
    vlTOPp->SOC__DOT__Processor__DOT__PCnext = ((1U 
                                                 & ((((IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes) 
                                                      >> 4U) 
                                                     & (IData)(vlTOPp->SOC__DOT__Processor__DOT__takeBranch)) 
                                                    | ((IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes) 
                                                       >> 5U)))
                                                 ? vlTOPp->SOC__DOT__Processor__DOT__PC_plus_imm
                                                 : 
                                                ((0x40U 
                                                  & (IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes))
                                                  ? 
                                                 (0xfffffffeU 
                                                  & vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__ALUadd)
                                                  : 
                                                 ((IData)(4U) 
                                                  + vlTOPp->SOC__DOT__Processor__DOT__PC)));
}

void VSOC::_eval_initial(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval_initial\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
    vlTOPp->_initial__TOP__3(vlSymsp);
}

void VSOC::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::final\n"); );
    // Variables
    VSOC__Syms* __restrict vlSymsp = this->__VlSymsp;
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VSOC::_eval_settle(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval_settle\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
    vlTOPp->_settle__TOP__4(vlSymsp);
}

void VSOC::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_ctor_var_reset\n"); );
    // Body
    i_clk = VL_RAND_RESET_I(1);
    i_rst = VL_RAND_RESET_I(1);
    o_leds = VL_RAND_RESET_I(3);
    RXD = VL_RAND_RESET_I(1);
    TXD = VL_RAND_RESET_I(1);
    SOC__DOT__IO_MEM_rdata = VL_RAND_RESET_I(32);
    SOC__DOT__Hw_LEDS = VL_RAND_RESET_I(3);
    { int __Vi0=0; for (; __Vi0<16384; ++__Vi0) {
            SOC__DOT__Processor__DOT__PROGROM[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<16384; ++__Vi0) {
            SOC__DOT__Processor__DOT__DATARAM[__Vi0] = VL_RAND_RESET_I(32);
    }}
    SOC__DOT__Processor__DOT__MEM_wdata = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__MEM_rdata = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__wMASK = VL_RAND_RESET_I(4);
    SOC__DOT__Processor__DOT__DATARAM_rdata = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__DATARAM_wmask = VL_RAND_RESET_I(4);
    SOC__DOT__Processor__DOT__PC = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__instr = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            SOC__DOT__Processor__DOT__REGISTERBANK[__Vi0] = VL_RAND_RESET_I(32);
    }}
    SOC__DOT__Processor__DOT__register_rs1 = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__register_rs2 = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__instrtypes = VL_RAND_RESET_I(10);
    SOC__DOT__Processor__DOT__imm = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__PC_plus_imm = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__ALU_in2 = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__takeBranch = VL_RAND_RESET_I(1);
    SOC__DOT__Processor__DOT__PCnext = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__loadstore_addr = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__LOAD_h = VL_RAND_RESET_I(16);
    SOC__DOT__Processor__DOT__LOAD_b = VL_RAND_RESET_I(8);
    SOC__DOT__Processor__DOT__LOAD_sign = VL_RAND_RESET_I(1);
    SOC__DOT__Processor__DOT__state = VL_RAND_RESET_I(2);
    SOC__DOT__Processor__DOT__ALU__DOT__shamt = VL_RAND_RESET_I(5);
    SOC__DOT__Processor__DOT__ALU__DOT__ALUsub = VL_RAND_RESET_Q(33);
    SOC__DOT__Processor__DOT__ALU__DOT__ALUadd = VL_RAND_RESET_I(32);
    SOC__DOT__Processor__DOT__ALU__DOT__LT = VL_RAND_RESET_I(1);
    __Vtableidx1 = 0;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[0] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[1] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[2] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[3] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[4] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[5] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[6] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[7] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[8] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[9] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[10] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[11] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[12] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[13] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[14] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[15] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[16] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[17] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[18] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[19] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[20] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[21] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[22] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[23] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[24] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[25] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[26] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[27] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[28] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[29] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[30] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[31] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[32] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[33] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[34] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[35] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[36] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[37] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[38] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[39] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[40] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[41] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[42] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[43] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[44] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[45] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[46] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[47] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[48] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[49] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[50] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[51] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[52] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[53] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[54] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[55] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[56] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[57] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[58] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[59] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[60] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[61] = 0U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[62] = 1U;
    __Vtable1_SOC__DOT__Processor__DOT__takeBranch[63] = 0U;
}
