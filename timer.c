#include "LPC1769.h"

void timer_Init(unsigned char timer, int prescaler){
	PCONP |= 1 << (1 + timer);			//set power control
	PCLKSEL |= 1 << (2 + timer * 2);	//set clock selection
	ISER1 |= 0xF << 4;					//enable interrupt

	timer_ClearIR(timer);
	timer_SetPR(timer, prescaler);
}

void timer_ClearIR(unsigned char timer){
	T_IR(timer) |= timer == PWM? 0x1F:0x73F;
}

void timer_Enable(unsigned char timer){
	T_TCR(timer) |= 0x1;
}

void timer_Disable(unsigned char timer){
	T_TCR(timer) &= ~0x1;
}

void timer_Reset(unsigned char timer){
	T_TCR(timer) |= 1 << 1;
}

void timer_SetPR(unsigned char timer, int prescaler){
	T_PR(timer) = prescaler;
}

void timer_SetMCR(unsigned char timer, unsigned char MR, unsigned char data){
	T_MCR(timer) |= data << (MR*3);
}

void timer_SetMR(unsigned char timer, unsigned char MR, short count){
	T_MR(timer, MR) = count;
}

