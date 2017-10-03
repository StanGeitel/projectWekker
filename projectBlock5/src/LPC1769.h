
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
#define PWM1PCR				(*(unsigned int *)	(0x4001804C))
#define PWM1LER				(*(unsigned int *)	(0x40018050))



//-------------------GPIO------------------//

#define GPIO_DIR(port)		(*(unsigned int *)	(0x2009C000 + 0x20 * port))
#define GPIO_MASK(port)		(*(unsigned int *)	(0x2009C010 + 0x20 * port))
#define GPIO_PIN(port)		(*(unsigned int *)	(0x2009C014 + 0x20 * port))
#define GPIO_SET(port)		(*(unsigned int *)	(0x2009C018 + 0x20 * port))
#define GPIO_CLR(port)		(*(unsigned int *)	(0x2009C01C + 0x20 * port))
#define GPIO_IntEnR(port)	(*(unsigned int *)	(0x40028090 + 0x10 * port))
#define GPIO_IntEnF(port)	(*(unsigned int *)	(0x40028094 + 0x10 * port))
#define GPIO_IntStatR(port)	(*(unsigned int *)	(0x40028084 + 0x10 * port))
#define GPIO_IntStatF(port)	(*(unsigned int *)	(0x40028088 + 0x10 * port))
#define GPIO_IntClt(port)	(*(unsigned int *)	(0x4002808C + 0x10 * port))
#define GPIO_IntStatus		(*(unsigned int *)	(0x40028080))

//-------------------------------

#define SSP				0x40088000
#define SSP_CR0			(*(unsigned int *)	(SSP))
#define SSP_CR1			(*(unsigned int *)	(SSP + 0x4))
#define SSP_DR			(*(unsigned int *)	(SSP + 0x8))
#define SSP_SR			(*(unsigned int *)	(SSP + 0xC))
#define SSP_CPSR		(*(unsigned int *)	(SSP + 0x10))
#define SSP_IMSC		(*(unsigned int *)	(SSP + 0x14))
#define SSP_RIS			(*(unsigned int *)	(SSP + 0x18))
#define SSP_MIS			(*(unsigned int *)	(SSP + 0x1C))
#define SSP_ICR			(*(unsigned int *)	(SSP + 0x20))

//------------------------------------

#define I2C		0x4005C000
#define I2C_CONSET  (*(unsigned int *)	(I2C)) // Control Set Register
#define I2C_STAT  	(*(unsigned int *)	(I2C + 0x4)) // status register
#define I2C_DAT  	(*(unsigned int *)	(I2C + 0x8)) // data register
#define I2C_SCLH  	(*(unsigned int *)	(I2C + 0x10)) // SCH Duty Cycle Register High Half Word
#define I2C_SCLL  	(*(unsigned int *)	(I2C + 0x14)) // SCL Duty Cycle Register Low Half Word
#define I2C_CONCLR  (*(unsigned int *)	(I2C + 0x18)) // clear control register

#endif







