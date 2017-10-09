#include "LPC1769.h"

void system_Init(void){
	system_SetClock();
	system_SetPinOut();
}

void system_Reset(void){
	AIRCR = 0x5FA << 16 | 1 << 2;	//feed
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
	PIN_SEL0 |= 0x300;
	PIN_SEL0 |= 1 << 31;
	PIN_SEL1 |= 1 << 5;
	PIN_SEL3 |= 1 << 22;
	PIN_SEL4 |= 1;
}
