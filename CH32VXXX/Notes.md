>-NOTE: Using the Baremetal example from (platform-ch32v)[https://github.com/Community-PIO-CH32V/platform-ch32v]
>- The Register's definitions were used, the functions are implemented using that scheme.

## Register Definition

```c
typedef struct
{
    __IO uint32_t CFGLR;
    __IO uint32_t CFGHR; // NOT IN THE DATASHET, used to offset the next address by 0x08 from the base_address
    __IO uint32_t INDR;
    __IO uint32_t OUTDR;
    __IO uint32_t BSHR;
    __IO uint32_t BCR;
    __IO uint32_t LCKR;
} GPIO_TypeDef;
```

`__IO` &rarr; `volatile`. With `volatile`, the compiler doesn't optimize the struct.

Then, the memory map is defined:

```c
#define FLASH_BASE                              ((uint32_t)0x08000000) /* FLASH base address in the alias region */
#define SRAM_BASE                               ((uint32_t)0x20000000) /* SRAM base address in the alias region */
#define PERIPH_BASE                             ((uint32_t)0x40000000) /* Peripheral base address in the alias region */

#define APB1PERIPH_BASE                         (PERIPH_BASE)
#define APB2PERIPH_BASE                         (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE                          (PERIPH_BASE + 0x20000)
```

With the peripheral base_address, the GPIOX base_address can be defined.

```c
#define GPIOA_BASE                              (APB2PERIPH_BASE + 0x0800)
#define GPIOC_BASE                              (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE                              (APB2PERIPH_BASE + 0x1400)
```

Finally, cast the addresses to `GPIO_Typedef`.

```c
#define GPIOA                                   ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOC                                   ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD                                   ((GPIO_TypeDef *)GPIOD_BASE)
```

## Simple GPIO functions

```c
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
	gpioPort->OUTDR &= ~(1 << pinNumber);
}
static inline void GPIO_PIN_TOGGLE(GPIO_TypeDef *gpioPort, uint8_t pinNumber) {
	gpioPort->OUTDR ^= 1 << pinNumber;
}
```

### GPIO init

```c
// 3.3.5.2 from ReferenceManual
/*
Each bit in the RCC_AHBPCENR, RCC_APB1PCENR, and RCC_APB2PCENR registers can be used to
individually turn on or off the communication clock interface for different peripheral modules. When using a
peripheral, you first need to turn on its clock enable bit in order to access its registers
*/
RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;
```

## RCC -> CLOCK

The `CH32V003` has an internal RC oscillator of 24MHz, an external clock can be used too.

The baremetal example just initialized the HSI.

Function to initialize the MCU with the HSE:

```c
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
```

## UART

`SetupUART( int uartBRR )` is used to init the peripheral.

Inside this function:

```c
USART1->BRR = uartBRR;
```

The BRR register is explained in section 12.3 Baud Rate Generator:

> The baud rate of the transceiver = HCLK/(16*USARTDIV), HCLK is the clock of AHB. The value of
USARTDIV is determined by the two fields DIV_M and DIV_F in USART_BRR, which is calculated by the
formula The formula is as follows. USARTDIV = DIV_M+(DIV_F/16)

- If the desired baudrate is 9600, and the clock is 48MHz &rarr;USART1->BRR = 5000 
- If the desired baudrate is 76800, and the clock is 48MHz &rarr;USART1->BRR = 625

Some baudrates are not obtainable, because USARTDIV may be a periodic decimal number, causing differences with a fraction division and giving a baudrate that is slightlt off.


Some functions were added to send data via UART:

```c
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
```

## Inline ASM

* [Inline Assembly Language - CDOT Wiki](https://wiki.cdot.senecacollege.ca/wiki/Inline_Assembly_Language)

```c
register int r_t2 asm("t2");
int c = 12 + 4;
asm volatile
(
    "addi	t0, x0, %[in]\n\t"
    "addi	%[out], t0, 4\n\t"
    : [out]"=r"(r_t2)   // outputs
    : [in]"i"(c)        // inputs
    : "t0", "t1"        // clobbers
);
```

Assembly output:

```s
	li	a5,16
	sw	a5,-20(s0)
	lw	a5,-20(s0)
#APP
# 6 "test_asm.c" 1
	addi	t0, x0, a5
	addi	t2, t0, 4
```

The above `.s` file was created with the following command(Inline ASM was used ):

```sh
riscv64-unknown-linux-gnu-gcc -S filename.c
```

The compiler decides certain optimizations and some registers, for example, `:[in]"i"(c)` indicates an immediate(`"i"`). The above command generated a `.s` file using `:[in]"r"(c)`, which indicates any general purpose register. And when a program is compiled with platformIO for the `ch32v003`, the general purpose register throws an error but not the immediate and vice versa with the `riscv64-gcc`

>-NOTE: some CSR registers of the CH32V003 are equal to zero.

### The cycle and instret CSRs

These registers are 64bit wide, they have a high and low part. The `RISCV Reference Manual` Recommends an specific loop to read the register. 

The CPI(Clocks Per Instruction) can be obtained as follows: $\text{CPI} = \cfrac{\text{cycle}}{\text{instret}}$

Care has to be taken, maybe a `long double` cast has to be applied to both registers and CPI should be a `long double` variable.

## QEMU

If QEMU-static is used, we can use the riscv64-gcc compiler with the `-static` flag, that executable file can then be run with:
 
```sh
sudo apt install qemu-user-static
```

```sh
riscv64-unknown-linux-gnu-gcc -static filename.c -o exe
```

```sh
qemu-riscv64-static exe
```
