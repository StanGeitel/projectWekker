/*
===============================================================================
 Name        : projectBlock5.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include "LPC1769.h"
#include "timer.h"
int test = 0;

int main(void) {
	//PIN_SEL0 |= 0x30F; //select pin sda1 (P0.0) and scl1 (P0.1) and CAP2.0 (P0.4)
	PIN_SEL0 |= 0x300; //select pin
	PIN_SEL0 |= 1 << 31;
	PIN_SEL1 |= 1 << 5;
	PIN_SEL4 |= 1 << 2;

	timer_Init(PWM,0);
	timer_SetMR(PWM,MR0,10);
	timer_SetMCR(PWM,MR0,0x2);
	timer_SetMR(PWM,MR2,5);
	timer_SetMCR(PWM,MR2,0x1);
	timer_EnablePWM(2);

	while(1);
}

void PWM1_IRQHandler(void){
	timer_ClearIR(PWM);
}


