// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSOC.h for the primary calling header

#include "VSOC.h"
#include "VSOC__Syms.h"

//==========

void VSOC::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VSOC::eval\n"); );
    VSOC__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("step1.v", 5, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void VSOC::_eval_initial_loop(VSOC__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("step1.v", 5, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void VSOC::_sequent__TOP__1(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_sequent__TOP__1\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v0;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v0;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v0;
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v1;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v1;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v1;
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v2;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v2;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v2;
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v3;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v3;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v3;
    CData/*4:0*/ __Vdlyvdim0__SOC__DOT__Processor__DOT__REGISTERBANK__v0;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__Processor__DOT__REGISTERBANK__v0;
    CData/*1:0*/ __Vdly__SOC__DOT__Processor__DOT__state;
    SData/*13:0*/ __Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v0;
    SData/*13:0*/ __Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v1;
    SData/*13:0*/ __Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v2;
    SData/*13:0*/ __Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v3;
    IData/*31:0*/ __Vdlyvval__SOC__DOT__Processor__DOT__REGISTERBANK__v0;
    IData/*31:0*/ __Vdly__SOC__DOT__Processor__DOT__instr;
    // Body
    __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v0 = 0U;
    __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v1 = 0U;
    __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v2 = 0U;
    __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v3 = 0U;
    __Vdly__SOC__DOT__Processor__DOT__state = vlTOPp->SOC__DOT__Processor__DOT__state;
    __Vdly__SOC__DOT__Processor__DOT__instr = vlTOPp->SOC__DOT__Processor__DOT__instr;
    __Vdlyvset__SOC__DOT__Processor__DOT__REGISTERBANK__v0 = 0U;
    if (VL_UNLIKELY((1U & (((vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr 
                             >> 0x16U) & (IData)(vlTOPp->SOC__DOT__Processor__DOT__wMASK)) 
                           & (vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr 
                              >> 2U))))) {
        VL_WRITEF("LEDS:%b\n",3,vlTOPp->SOC__DOT__Hw_LEDS);
        vlTOPp->SOC__DOT__Hw_LEDS = (7U & vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata);
    }
    vlTOPp->SOC__DOT__Processor__DOT__DATARAM_rdata 
        = vlTOPp->SOC__DOT__Processor__DOT__DATARAM
        [(0x3fffU & (vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr 
                     >> 2U))];
    if ((1U & (IData)(vlTOPp->SOC__DOT__Processor__DOT__DATARAM_wmask))) {
        __Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v0 
            = (0xffU & vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata);
        __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v0 = 1U;
        __Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v0 = 0U;
        __Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v0 
            = (0x3fffU & (vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr 
                          >> 2U));
    }
    if ((2U & (IData)(vlTOPp->SOC__DOT__Processor__DOT__DATARAM_wmask))) {
        __Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v1 
            = (0xffU & (vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata 
                        >> 8U));
        __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v1 = 1U;
        __Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v1 = 8U;
        __Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v1 
            = (0x3fffU & (vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr 
                          >> 2U));
    }
    if ((4U & (IData)(vlTOPp->SOC__DOT__Processor__DOT__DATARAM_wmask))) {
        __Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v2 
            = (0xffU & (vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata 
                        >> 0x10U));
        __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v2 = 1U;
        __Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v2 = 0x10U;
        __Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v2 
            = (0x3fffU & (vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr 
                          >> 2U));
    }
    if ((8U & (IData)(vlTOPp->SOC__DOT__Processor__DOT__DATARAM_wmask))) {
        __Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v3 
            = (0xffU & (vlTOPp->SOC__DOT__Processor__DOT__MEM_wdata 
                        >> 0x18U));
        __Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v3 = 1U;
        __Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v3 = 0x18U;
        __Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v3 
            = (0x3fffU & (vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr 
                          >> 2U));
    }
    if (((((((1U == (IData)(vlTOPp->SOC__DOT__Processor__DOT__state)) 
             & (~ ((IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes) 
                   >> 2U))) & (~ ((IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes) 
                                  >> 3U))) & (~ ((IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes) 
                                                 >> 4U))) 
          | (3U == (IData)(vlTOPp->SOC__DOT__Processor__DOT__state))) 
         & (0U != (0x1fU & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                            >> 7U))))) {
        __Vdlyvval__SOC__DOT__Processor__DOT__REGISTERBANK__v0 
            = ((1U & (((IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes) 
                       >> 5U) | ((IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes) 
                                 >> 6U))) ? ((IData)(4U) 
                                             + vlTOPp->SOC__DOT__Processor__DOT__PC)
                : ((0x80U & (IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes))
                    ? vlTOPp->SOC__DOT__Processor__DOT__imm
                    : ((0x100U & (IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes))
                        ? vlTOPp->SOC__DOT__Processor__DOT__PC_plus_imm
                        : ((4U & (IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes))
                            ? ((0U == (3U & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                             >> 0xcU)))
                                ? ((0xffffff00U & (
                                                   (- (IData)((IData)(vlTOPp->SOC__DOT__Processor__DOT__LOAD_sign))) 
                                                   << 8U)) 
                                   | (IData)(vlTOPp->SOC__DOT__Processor__DOT__LOAD_b))
                                : ((1U == (3U & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                 >> 0xcU)))
                                    ? ((0xffff0000U 
                                        & ((- (IData)((IData)(vlTOPp->SOC__DOT__Processor__DOT__LOAD_sign))) 
                                           << 0x10U)) 
                                       | (IData)(vlTOPp->SOC__DOT__Processor__DOT__LOAD_h))
                                    : vlTOPp->SOC__DOT__Processor__DOT__MEM_rdata))
                            : ((0x4000U & vlTOPp->SOC__DOT__Processor__DOT__instr)
                                ? ((0x2000U & vlTOPp->SOC__DOT__Processor__DOT__instr)
                                    ? ((0x1000U & vlTOPp->SOC__DOT__Processor__DOT__instr)
                                        ? (vlTOPp->SOC__DOT__Processor__DOT__register_rs1 
                                           & vlTOPp->SOC__DOT__Processor__DOT__ALU_in2)
                                        : (vlTOPp->SOC__DOT__Processor__DOT__register_rs1 
                                           | vlTOPp->SOC__DOT__Processor__DOT__ALU_in2))
                                    : ((0x1000U & vlTOPp->SOC__DOT__Processor__DOT__instr)
                                        ? ((0x40000000U 
                                            & vlTOPp->SOC__DOT__Processor__DOT__instr)
                                            ? VL_SHIFTRS_III(32,32,5, vlTOPp->SOC__DOT__Processor__DOT__register_rs1, (IData)(vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__shamt))
                                            : (vlTOPp->SOC__DOT__Processor__DOT__register_rs1 
                                               >> (IData)(vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__shamt)))
                                        : (vlTOPp->SOC__DOT__Processor__DOT__register_rs1 
                                           ^ vlTOPp->SOC__DOT__Processor__DOT__ALU_in2)))
                                : ((0x2000U & vlTOPp->SOC__DOT__Processor__DOT__instr)
                                    ? ((0x1000U & vlTOPp->SOC__DOT__Processor__DOT__instr)
                                        ? (1U & (IData)(
                                                        (vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__ALUsub 
                                                         >> 0x20U)))
                                        : (IData)(vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__LT))
                                    : ((0x1000U & vlTOPp->SOC__DOT__Processor__DOT__instr)
                                        ? (vlTOPp->SOC__DOT__Processor__DOT__register_rs1 
                                           << (IData)(vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__shamt))
                                        : ((1U & ((vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                   >> 0x1eU) 
                                                  & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                                                     >> 5U)))
                                            ? (IData)(vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__ALUsub)
                                            : vlTOPp->SOC__DOT__Processor__DOT__ALU__DOT__ALUadd))))))));
        __Vdlyvset__SOC__DOT__Processor__DOT__REGISTERBANK__v0 = 1U;
        __Vdlyvdim0__SOC__DOT__Processor__DOT__REGISTERBANK__v0 
            = (0x1fU & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                        >> 7U));
    }
    if (__Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v0) {
        vlTOPp->SOC__DOT__Processor__DOT__DATARAM[__Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v0] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v0))) 
                & vlTOPp->SOC__DOT__Processor__DOT__DATARAM
                [__Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v0]) 
               | ((IData)(__Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v0) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v0)));
    }
    if (__Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v1) {
        vlTOPp->SOC__DOT__Processor__DOT__DATARAM[__Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v1] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v1))) 
                & vlTOPp->SOC__DOT__Processor__DOT__DATARAM
                [__Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v1]) 
               | ((IData)(__Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v1) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v1)));
    }
    if (__Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v2) {
        vlTOPp->SOC__DOT__Processor__DOT__DATARAM[__Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v2] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v2))) 
                & vlTOPp->SOC__DOT__Processor__DOT__DATARAM
                [__Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v2]) 
               | ((IData)(__Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v2) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v2)));
    }
    if (__Vdlyvset__SOC__DOT__Processor__DOT__DATARAM__v3) {
        vlTOPp->SOC__DOT__Processor__DOT__DATARAM[__Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v3] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v3))) 
                & vlTOPp->SOC__DOT__Processor__DOT__DATARAM
                [__Vdlyvdim0__SOC__DOT__Processor__DOT__DATARAM__v3]) 
               | ((IData)(__Vdlyvval__SOC__DOT__Processor__DOT__DATARAM__v3) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__Processor__DOT__DATARAM__v3)));
    }
    vlTOPp->o_leds = vlTOPp->SOC__DOT__Hw_LEDS;
    if ((0U == (IData)(vlTOPp->SOC__DOT__Processor__DOT__state))) {
        __Vdly__SOC__DOT__Processor__DOT__state = 2U;
        __Vdly__SOC__DOT__Processor__DOT__instr = vlTOPp->SOC__DOT__Processor__DOT__PROGROM
            [(0x3fffU & (vlTOPp->SOC__DOT__Processor__DOT__PC 
                         >> 2U))];
    } else {
        if ((2U == (IData)(vlTOPp->SOC__DOT__Processor__DOT__state))) {
            vlTOPp->SOC__DOT__Processor__DOT__register_rs1 
                = vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK
                [(0x1fU & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                           >> 0xfU))];
            __Vdly__SOC__DOT__Processor__DOT__state = 1U;
            vlTOPp->SOC__DOT__Processor__DOT__register_rs2 
                = vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK
                [(0x1fU & (vlTOPp->SOC__DOT__Processor__DOT__instr 
                           >> 0x14U))];
        } else {
            if ((1U == (IData)(vlTOPp->SOC__DOT__Processor__DOT__state))) {
                if ((1U & (~ ((IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes) 
                              >> 9U)))) {
                    vlTOPp->SOC__DOT__Processor__DOT__PC 
                        = vlTOPp->SOC__DOT__Processor__DOT__PCnext;
                }
                __Vdly__SOC__DOT__Processor__DOT__state 
                    = ((4U & (IData)(vlTOPp->SOC__DOT__Processor__DOT__instrtypes))
                        ? 3U : 0U);
            } else {
                __Vdly__SOC__DOT__Processor__DOT__state = 0U;
            }
        }
    }
    if (__Vdlyvset__SOC__DOT__Processor__DOT__REGISTERBANK__v0) {
        vlTOPp->SOC__DOT__Processor__DOT__REGISTERBANK[__Vdlyvdim0__SOC__DOT__Processor__DOT__REGISTERBANK__v0] 
            = __Vdlyvval__SOC__DOT__Processor__DOT__REGISTERBANK__v0;
    }
    vlTOPp->SOC__DOT__Processor__DOT__state = __Vdly__SOC__DOT__Processor__DOT__state;
    vlTOPp->SOC__DOT__Processor__DOT__instr = __Vdly__SOC__DOT__Processor__DOT__instr;
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
    vlTOPp->SOC__DOT__Processor__DOT__PC_plus_imm = 
        (vlTOPp->SOC__DOT__Processor__DOT__PC + vlTOPp->SOC__DOT__Processor__DOT__imm);
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
    vlTOPp->SOC__DOT__Processor__DOT__DATARAM_wmask 
        = ((IData)(vlTOPp->SOC__DOT__Processor__DOT__wMASK) 
           & (- (IData)((1U & (~ (vlTOPp->SOC__DOT__Processor__DOT__loadstore_addr 
                                  >> 0x16U))))));
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

void VSOC::_eval(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->i_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__i_clk)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
}

VL_INLINE_OPT QData VSOC::_change_request(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_change_request\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData VSOC::_change_request_1(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_change_request_1\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void VSOC::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((i_clk & 0xfeU))) {
        Verilated::overWidthError("i_clk");}
    if (VL_UNLIKELY((i_rst & 0xfeU))) {
        Verilated::overWidthError("i_rst");}
    if (VL_UNLIKELY((RXD & 0xfeU))) {
        Verilated::overWidthError("RXD");}
}
#endif  // VL_DEBUG
