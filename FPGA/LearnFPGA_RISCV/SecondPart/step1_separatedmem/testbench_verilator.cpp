#include "VSOC.h"
#include "verilated.h"
#include <iostream>


int main(int argc, char const *argv[])
{
    VSOC top;
    top.i_clk = 0;
    while(!Verilated::gotFinish()){
        top.i_clk = !top.i_clk;
        top.eval();
    }
    return 0;
}
