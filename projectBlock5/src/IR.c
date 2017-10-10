#include "LPC1769.h"
#include "timer.h"
#include "GPIO.h"
#include "IR.h"
#include "alarm.h"
#include "RealTimeClock.h"
#include "display.h"
#include <stdio.h>

#define DELAY 400

unsigned char bit = 0;
short data = 0;
unsigned char prevData = -1;
int startTime;


void IR_Init(void){
	timer_Init(IR_TIMER,119);
	timer_SetCCR(IR_TIMER,IR_CAPTURE,0x5);
	timer_Enable(IR_TIMER);

	GPIO_Int_EnableF(IR_IOPORT,1 << IR_PIN);
	GPIO_Int_Init(IR_IOPORT);
}

void TIMER2_IRQHandler(void){
	timer_ClearIR(IR_TIMER);

	int time = timer_GetCR(IR_TIMER, IR_CAPTURE);
	PIN_SEL0 &= ~(0x3 << 8); 	//set pin as GPIO

		if(time < MAX_TIME_BIT0 && time > MIN_TIME_BIT0){
			bit++;
		}else if(time < MAX_TIME_BIT1 && time > MIN_TIME_BIT1){
			data |= 1 << bit;
			bit++;
		}else if(time < MAX_TIME_STARTBIT && time > MIN_TIME_STARTBIT){
			bit = 0;
			data = 0;
		}

	if(bit == SIRC_LENGTH){
		data = data & 0x7F;

		if(data != prevData){
			startTime = timer_GetCount(MILIS_TIMER);
			prevData = data;

		}else if((timer_GetCount(MILIS_TIMER) - startTime) > DELAY){
			startTime = timer_GetCount(MILIS_TIMER);

		}
	}
}

void EINT3_IRQHandler(void){
	timer_Reset(IR_TIMER);
	GPIO_Int_Clear(IR_IOPORT, 1 << IR_PIN);
	PIN_SEL0 |= 0x3 << 8;								//set pin as capture pin
}

