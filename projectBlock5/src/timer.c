#include "LPC1769.h"
#include "timer.h"

void timer_Init(unsigned char timer, int prescaler){
	switch(timer){
	case TIMER0:
		PCONP |= 1 << 1;
		PCLKSEL0 |= 1 << 2;
		ISER0 |= 1 << 1;
	case TIMER1:
		PCONP |= 1 << 2;
		PCLKSEL0 |= 1 << 4;
		ISER0 |= 1 << 2;
	case TIMER2:
		PCONP |= 1 << 22;
		PCLKSEL1 |= 1 << 12;
		ISER0 |= 1 << 3;
	case TIMER3:
		PCONP |= 1 << 14;
		PCLKSEL1 |= 1 << 2;
		ISER0 |= 1 << 4;
	case PWM:
		PCONP |= 1 << 6;
		PCLKSEL0 |= 1 << 12;
		ISER0 |= 1 << 9;
	}
	timer_ClearIR(timer);
	timer_SetPR(timer, prescaler);
}

void timer_ClearIR(unsigned char timer){
	T_IR(timer) |= 0x1F;
}

void timer_Enable(unsigned char timer){
	T_TCR(timer) &= ~0x3;
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
	T_MCR(timer) &= ~0x7 << (MR*3);
	T_MCR(timer) |= data << (MR*3);
}

void timer_SetMR(unsigned char timer, unsigned char MR, short count){
	T_MR(timer, MR) = count;
}

int timer_GetCount(unsigned char timer){
	return T_TC(timer);
}

void timer_SetCTCR(unsigned char timer, unsigned char mode, unsigned char cap){
	T_CTCR(timer) |= mode + cap << 2;
}

void timer_EnablePWM(unsigned char channels){
	T_TCR(PWM) |= 0x9;
	PWM1PCR |= channels << 9;
}

void timer_SetPWMMR(unsigned char MR, unsigned char count){
	T_MR(PWM, MR) = count;
	PWM1LER |= 1 << MR;
}

void timer_IncreasePWMMR(unsigned char MR){
	T_MR(PWM, MR)++;
	PWM1LER |= 1 << MR;
}

void timer_DecreasePWMMR(unsigned char MR){
	T_MR(PWM, MR)--;
	PWM1LER |= 1 << MR;
}

short timer_GetMR(unsigned char timer, unsigned char MR){
	return T_MR(PWM, MR);
}
