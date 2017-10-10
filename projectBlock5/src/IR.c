#include "LPC1769.h"
#include "timer.h"
#include "GPIO.h"
#include "IR.h"
#include "alarm.h"
#include "RealTimeClock.h"
#include "display.h"
#include <stdio.h>

unsigned char bit = 0;
short data = 0;


void IR_Init(void){
	timer_Init(IR_TIMER,3);
	timer_SetCCR(IR_TIMER,IR_CAPTURE,0x5);
	timer_Enable(IR_TIMER);

	GPIO_Int_EnableF(IR_IOPORT,1 << IR_PIN);
	GPIO_Int_Init(IR_IOPORT);
}

void TIMER2_IRQHandler(void){
	timer_ClearIR(IR_TIMER);

	int time = timer_GetCR(IR_TIMER, IR_CAPTURE);
	PIN_SEL0 &= ~(0x3 << 8); 	//set pin as GPIO

	if(bit < SIRC_LENGTH){
		if(time < MAX_TIME_BIT0 && time > MIN_TIME_BIT0){
			bit++;
		}else if(time < MAX_TIME_BIT1 && time > MIN_TIME_BIT1){
			data |= 1 << bit;
			bit++;
		}else if(time < MAX_TIME_STARTBIT && time > MIN_TIME_STARTBIT){
			bit = 0;
			data = 0;
		}
	}else if(bit == SIRC_LENGTH){
		data = (data & ~0x1F) >> 5;
		printf("button: %d", data + 1);
		alarm_SetButton(data + 1);
	}
}

void EINT3_IRQHandler(void){
	timer_Reset(IR_TIMER);
	GPIO_Int_Clear(IR_IOPORT, 1 << IR_PIN);					//set pin as capture pin
	PIN_SEL0 |= 0x3 << 8;								//set pin as capture pin
}

