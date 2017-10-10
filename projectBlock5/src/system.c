#include "LPC1769.h"

void system_Init(void){
	system_SetClock();
	system_SetPinOut();
	system_SetIntPriority();
}

void system_Reset(void){
	AIRCR = 0x5FA << 16 | 1 << 2;
}

void system_SetClock(void){
	CLKOUTCFG |= 272;		//enable clock out
	PIN_SEL4 |= 1 << 2;		//set pin clock out

	SCS |= 1 << 5;			//enable main oscillator

	PLL_CON &= ~2;		//disconnect pll
	PLL_FEED |=	0xAA;
	PLL_FEED |= 0x55;

	PLL_CON &= ~1;		//disable pll
	PLL_FEED |=	0xAA;
	PLL_FEED |= 0x55;

	while(!((SCS >> 6) & 1));	//wait for main osc to stabalize

	CLKSRCSEL |= 1;		//select main osc

	PLL_CFG |= 0x0E;	//set n and m
	PLL_FEED |=	0xAA;
	PLL_FEED |= 0x55;

	PLL_CON |= 1;		//enalbe pll
	PLL_FEED |=	0xAA;
	PLL_FEED |= 0x55;

	CCLKCFG |= 2;		//set clk div

	while(!((PLL_STAT >> 26) & 1));	//wait for lock

	PLL_CON |= 2;		//connect pll
	PLL_FEED |=	0xAA;
	PLL_FEED |= 0x55;
}

void system_SetPinOut(void){
	PIN_SEL0 = 1 << 31;	//P0.15 -> SCK;
	PIN_SEL1 = 1 << 5;		//P0.18 -> MOSI0
	PIN_SEL1 |= 3 << 16;	//P0.24 -> CAP3.1
	PIN_SEL1 |= 1 << 22;	//P0.27 -> SDA0
	PIN_SEL1 |= 1 << 24;	//P0.28 -> SCL0
	PIN_SEL4 = 1 << 2;		//P2.1 -> PWM1.2
}

void system_SetIntPriority(void){
	IPR5 = 1 << 11;		//EINT3 = 1	(ir-faling)
	IPR0 = 2 << 11;		//TIMER0 = 2(ir-rising)
	IPR0 |= 3 << 27;	//TIMER2 = 3(sound)
	IPR7 = 4 << 11;		//RIT = 4	(display)
	IPR1 = 5 << 3;		//TIMER3 = 5(RTC)

	IPR0 |= 9 << 19;	//TIMER1 = 9
}
