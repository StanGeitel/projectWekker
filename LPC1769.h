
#ifndef LPC1769_H_
#define LPC1769_H_

#define PCONP		(*(unsigned int *)	(0x400FC0C4))
#define PCLKSEL0	(*(unsigned int *)	(0x400FC1A8))
#define PCLKSEL1	(*(unsigned int *)	(0x400FC1AC))
#define ISER0		(*(unsigned int *)	(0xE000E100))
#define ISER1		(*(unsigned int *)	(0xE000E104))

#define PIN_SEL0	(*(unsigned int *)	(0x4002C000))
#define PIN_SEL1	(*(unsigned int *)	(0x4002C004))
#define PIN_SEL2	(*(unsigned int *)	(0x4002C008))
#define PIN_SEL3	(*(unsigned int *)	(0x4002C00C))
#define PIN_SEL4	(*(unsigned int *)	(0x4002C010))
#define PIN_SEL7	(*(unsigned int *)	(0x4002C01C))
#define PIN_SEL8	(*(unsigned int *)	(0x4002C020))
#define PIN_SEL9	(*(unsigned int *)	(0x4002C024))
#define PIN_SEL10	(*(unsigned int *)	(0x4002C028))
#define PIN_MODE0	(*(unsigned int *)	(0x4002C040))
#define PIN_MODE1	(*(unsigned int *)	(0x4002C044))
#define PIN_MODE2	(*(unsigned int *)	(0x4002C048))
#define PIN_MODE3	(*(unsigned int *)	(0x4002C04C))
#define PIN_MODE4	(*(unsigned int *)	(0x4002C050))
#define PIN_MODE5	(*(unsigned int *)	(0x4002C054))
#define PIN_MODE6	(*(unsigned int *)	(0x4002C058))
#define PIN_MODE7	(*(unsigned int *)	(0x4002C05C))
#define PIN_MODE9	(*(unsigned int *)	(0x4002C064))
#define PIN_MODEOD0	(*(unsigned int *)	(0x4002C068))
#define PIN_MODEOD1	(*(unsigned int *)	(0x4002C06C))
#define PIN_MODEOD2	(*(unsigned int *)	(0x4002C070))
#define PIN_MODEOD3	(*(unsigned int *)	(0x4002C074))
#define PIN_MODEOD4	(*(unsigned int *)	(0x4002C078))
#define I2C_PADCFG	(*(unsigned int *)	(0x4002C07C))

//-----------------TIMER------------------//
#define TIMER0	0
#define TIMER1	1
#define TIMER2	23
#define TIMER3	24
#define	MR0		0
#define	MR1		1
#define	MR2		2
#define	MR3		3
#define M4		10
#define M5		11
#define M6		12
#define CR0		0
#define CR1		1
#define CR2		2
#define CR3		3

#define T(n) (0x40004000 + (0x4000 * n))
#define T_IR(timer) 	(*(unsigned int *)	(T(timer)))
#define T_TCR(timer)	(*(unsigned int *)	(T(timer) + 0x4))
#define T_TC(timer)		(*(unsigned int *)	(T(timer) + 0x8))
#define T_PR(timer) 	(*(unsigned int *)	(T(timer) + 0xC))
#define T_PC(timer) 	(*(unsigned int *)	(T(timer) + 0x10))
#define T_MCR(timer) 	(*(unsigned int *)	(T(timer) + 0x14))
#define T_MR(timer, MR) (*(unsigned int *)	(T(timer) + 0x18 + (MR * 0x4)))
#define T_CCR(timer) 	(*(unsigned int *)	(T(timer) + 0x28))
#define T_CR(timer, CR) (*(unsigned int *)	(T(timer) + 0x2C + (CR * 0x4)))
#define T_EMR(timer) 	(*(unsigned int *)	(T(timer) + 0x3C))
#define T_CTCR(timer) 	(*(unsigned int *)	(T(timer) + 0x70))
#define PCR				(*(unsigned int *)	(T(timer) + 0x4C))
#define LER				(*(unsigned int *)	(T(timer) + 0x50))
#define CTCR			(*(unsigned int *)	(T(timer) + 0x70))

void timer_Init(unsigned char timer, int prescaler);
void timer_ClearIR(unsigned char timer);
void timer_Enable(unsigned char timer);
void timer_Disable(unsigned char timer);
void timer_Reset(unsigned char timer);
void timer_SetPR(unsigned char timer, int prescaler);
void timer_SetMCR(unsigned char timer, unsigned char MR, unsigned char data);
void timer_SetMR(unsigned char timer, unsigned char MR, short count);



//-------------------GPIO------------------//
#define PORT0	0
#define PORT1	1
#define PORT2	2
#define PORT3	3

#define GPIO_DIR(port)		(*(unsigned int *)	(0x2009C000 + 0x20 * port))
#define GPIO_MASK(port)		(*(unsigned int *)	(0x2009C010 + 0x20 * port))
#define GPIO_PIN(port)		(*(unsigned int *)	(0x2009C014 + 0x20 * port))
#define GPIO_SET(port)		(*(unsigned int *)	(0x2009C018 + 0x20 * port))
#define GPIO_CLR(port)		(*(unsigned int *)	(0x2009C01C + 0x20 * port))
#define GPIO_IntEnR(port)	(*(unsigned int *)	(0x2009C090 + 0x10 * port))
#define GPIO_IntEnF(port)	(*(unsigned int *)	(0x2009C094 + 0x10 * port))
#define GPIO_IntStatR(port)	(*(unsigned int *)	(0x2009C084 + 0x10 * port))
#define GPIO_IntStatF(port)	(*(unsigned int *)	(0x2009C088 + 0x10 * port))
#define GPIO_IntClt(port)	(*(unsigned int *)	(0x2009C08C + 0x10 * port))
#define GPIO_IntStatus		(*(unsigned int *)	(0x40028080))

#define GPIO0_IntPins		0x7FFF8FFF
#define GPIO2_IntPins		0x3FF

void GPIO_Init(unsigned char port, int DIR, int pins);
void GPIO_Int_Init(void);
void GPIO_Set(unsigned char port, int pins);
void GPIO_Clear(unsigned char port, int pins);
void GPIO_Toggle(unsigned char port,int pins);
int GPIO_Read(unsigned char port);
void GPIO_Int_Clear(unsigned char port, int pins);
void GPIO_Int_EnableR(unsigned char port, int pins);
void GPIO_Int_EnableF(unsigned char port, int pins);
int GPIO_Int_StatusR(unsigned char port, int pins);
int GPIO_Int_StatusF(unsigned char port, int pins);

#endif







