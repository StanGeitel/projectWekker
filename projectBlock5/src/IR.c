#include "LPC1769.h"
#include "timer.h"
#include "GPIO.h"
#include "IR.h"

unsigned char bit = 0;

void IR_Init(void){
	timer_Init(IR_TIMER,3999);
	timer_SetCCR(IR_TIMER,IR_CAPTURE,0x5);
	timer_Enable(IR_TIMER);
}

void TIMER0_IRQHandler(void){
	timer_ClearIR(IR_TIMER);

	int time = timer_GetCCR(IR_TIMER, IR_CAPTURE);
	if(bit < SIRC_LENGTH){
		if(time < MAX_TIME_BIT0 && time > MIN_TIME_BIT0){
			bit++;
		}else if(time < MAX_TIME_BIT1 && time > MIN_TIME_BIT1){
			data |= 1 << bit;
			bit++;
		}else if(time < MAX_TIME_STARTBIT && time > MAX_TIME_STARTBIT){
			bit = 0;
			data = 0;
		}
	}else if(bit == SIRC_LENGTH){
		data & 0x7F;
	}

	timer_Reset(IR_TIMER);
}
