#include "stdio.h"



long long int read_instretl(void)
{
	long long int instretl;
	asm volatile("rdinstret %[outl]\n\t": [outl]"=r"(instretl));
	return instretl;
}

long long int read_cyclel(void)
{
	long long int cyclel;
	asm volatile ("rdcycle %[outl]\n\t": [outl]"=r"(cyclel));
	return cyclel;
}

int main(int argc, char const *argv[])
{
    long long int cycle = read_cyclel();
    long long int instret = read_instretl();

    
    printf("cycle: 0x%llX\n", cycle);
    printf("instret: 0x%llX\n", instret);

    long double cpi = (long double)cycle/(long double)instret * 100;
    printf("CPI: %Lf\n", cpi);
    return 0;
}
cpi