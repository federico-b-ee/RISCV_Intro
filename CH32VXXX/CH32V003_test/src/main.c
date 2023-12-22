// Could be defined here, or in the processor defines.
#define SYSTEM_CORE_CLOCK 48000000

#include "ch32v00x.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APB_CLOCK SYSTEM_CORE_CLOCK

#define TRUE	1
#define FALSE	0
#define BPS9600 5000 // uartBRR
#define BPS76800 625 // uartBRR

void configureGPIO_OUT(GPIO_TypeDef *gpioPort, uint8_t pinNumber, uint8_t initState) {
    // Clear the configuration bits for the specified pin
    gpioPort->CFGLR &= ~(0xf << (4 * pinNumber));
    // Set the new configuration for the specified pin
    gpioPort->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP) << (4 * pinNumber);
	// Set it to a known state
	if (initState == 1) 
	{
		gpioPort->BSHR |= 1 << pinNumber;
	}
	else
	{
		gpioPort->BCR |= 1 << pinNumber;
	}
	
}
// Function to turn on a specific bit in the BSHR register
// RESET and SET register
static inline void GPIO_ON_BSHR(GPIO_TypeDef *gpioPort, uint8_t pinNumber) {
    gpioPort->BSHR |= 1 << pinNumber;
}
// Function to turn off a specific bit in the BCR register
// RESET register
static inline void GPIO_OFF_BCR(GPIO_TypeDef *gpioPort, uint8_t pinNumber) {
	gpioPort->BCR |= 1 << pinNumber;
}
// Function to Write the GPIOx port
// OUTDR register
static inline void GPIO_PORT_WRITE(GPIO_TypeDef *gpioPort, uint16_t number) {
	gpioPort->OUTDR = number;
}
// Functions to handle GPIO operations. Using OUTDR is more convenient than BCR and BSHR
// OUTDR register
static inline void GPIO_PIN_ON(GPIO_TypeDef *gpioPort, uint8_t pinNumber) {
	gpioPort->OUTDR |= 1 << pinNumber;
}
static inline void GPIO_PIN_OFF(GPIO_TypeDef *gpioPort, uint8_t pinNumber) {
	gpioPort->OUTDR |= 0 << pinNumber;
}
static inline void GPIO_PIN_TOGGLE(GPIO_TypeDef *gpioPort, uint8_t pinNumber) {
	gpioPort->OUTDR ^= 1 << pinNumber;
}

// The system defaults HSION and HSIRDY to 1 (it is recommended not to turn them off)
// Note: If the HSE crystal oscillator fails, the HSI clock is used as a backup clock source (clock safety system).
void SystemInit48HSE( void )
{
	RCC->CTLR  = RCC_HSEON | RCC_PLLON; 				// External CLOCK  == 24MHz
	RCC->CFGR0 = RCC_HPRE_DIV1 | RCC_PLLSRC_HSI_Mul2;	// PLL *2
	
	// From SystemInit48HSI
	FLASH->ACTLR = FLASH_ACTLR_LATENCY_1;				// 1 Cycle Latency
	RCC->INTR  = 0x009F0000;                            // Clear PLL, CSSC, HSE, HSI and LSI Inrerrupt Enable ready flags.

	while((RCC->CTLR & RCC_HSERDY) == 0);														// Wait till HSE is stable
	// From SetSysClockTo_48MHZ_HSI
	while((RCC->CTLR & RCC_PLLRDY) == 0);														// Wait till PLL is ready
	RCC->CFGR0 = ( RCC->CFGR0 & ((uint32_t)~(RCC_SW))) | (uint32_t)RCC_SW_PLL;					// Select PLL as system clock source
	while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08);									// Wait till PLL is used as system clock source
}

void USART_putc(char c)
{
	while(!(USART1->STATR & USART_FLAG_TC));
	USART1->DATAR = c;
}

void USART_printf(char *buf, uint8_t len)
{
	uint8_t i = 0;
	for (i = 0; i < len; i++)
	{
		USART_putc(buf[i]);
	}
}

int read_instreth(void)
{
	int instreth;
	asm volatile("rdinstreth %[outh]\n\t": [outh]"=r"(instreth));
	return instreth;
}

int read_instretl(void)
{
	int instretl;
	asm volatile("rdinstret %[outl]\n\t": [outl]"=r"(instretl));
	return instretl;
}

int read_cycleh(void)
{
	int cycleh;
	asm volatile("rdcycleh %[outh]\n\t": [outh]"=r"(cycleh));
	return cycleh;
}

int read_cyclel(void)
{
	int cyclel;
	asm volatile ("rdcycle %[outl]\n\t": [outl]"=r"(cyclel));
	return cyclel;
}

int read_misa(void)
{
	int misa;
	asm volatile("csrr %[out], misa\n\t": [out]"=r"(misa));
	return misa;
}

static char * _float_to_char(float x, char *p, int len) {
    char *s = p + len; // go to end of buffer
    uint16_t decimals;  // variable to store the decimals
    int units;  // variable to store the units (part to left of decimal place)

    decimals = (int)(x * 100) % 100;
    units = (int)x;

    *--s = (decimals % 10) + '0';
    decimals /= 10; // repeat for as many decimal places as you need
    *--s = (decimals % 10) + '0';
    *--s = '.';

    while (units > 0) {
        *--s = (units % 10) + '0';
        units /= 10;
    }
    if (x < 0) *--s = '-'; // unary minus sign for negative numbers
    return s;
}

int main()
{
	SystemInit48HSE();
	SetupUART(BPS76800);

	// 3.3.5.2 from ReferenceManual
	/*
	Each bit in the RCC_AHBPCENR, RCC_APB1PCENR, and RCC_APB2PCENR registers can be used to
	individually turn on or off the communication clock interface for different peripheral modules. When using a
	peripheral, you first need to turn on its clock enable bit in order to access its registers
	*/
	RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;

	configureGPIO_OUT(GPIOC, 1, TRUE);
	configureGPIO_OUT(GPIOC, 2, TRUE);

	char buf[80] = "TEST";

    register int r_t2 asm("t2");
    int c = 16;
    asm volatile
	(
		"addi	t0, x0, %[in]\n\t"
		"addi	%[out], t0, 4\n\t"
		: [out]"=r"(r_t2)
		: [in]"i"(c)
		: "t0", "t1"
	);

	uint64_t instret;
	uint64_t cycle;
	float cpi;


	int len = 20;
	char result[len];
	char s_cycle[len];
	char s_instret[len];

	memset(result, 0, len);
	memset(s_cycle, 0, len);
	memset(s_instret, 0, len);

	while(1)
	{
		//instret = read_instreth() << 32 | read_instretl();
		//cycle = read_cycleh() << 32 | read_cyclel();
		//cpi = (cycle/instret);

		itoa(read_misa(), s_cycle, 16);
		itoa(read_cyclel(), s_instret, 10);

		

		//USART_printf(_float_to_char(cpi, result, len), 9);
		
		//USART_printf("Cycles:");
		USART_putc('0');		
		USART_putc('x');
		USART_printf(s_cycle, strlen(s_cycle));
		USART_putc('$');

		
		GPIO_PIN_TOGGLE(GPIOC, 1);
		Delay_Ms( 100 );
		GPIO_PIN_TOGGLE(GPIOC, 1);
		Delay_Ms( 100 );
	}
}


