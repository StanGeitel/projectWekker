#include "LPC1769.h"
#include "timer.h"
#include "GPIO.h"
#include "IR.h"

unsigned char bit = 0;
short data = 0;

void IR_Init(void){
	GPIO_Int_Init(IR_IOPORT);
	GPIO_Int_EnableF(IR_IOPORT,1 << IR_PIN);

	timer_Init(IR_TIMER,3999);
	timer_SetCCR(IR_TIMER,IR_CAPTURE,0x5);
	timer_Enable(IR_TIMER);
}

void TIMER2_IRQHandler(void){
	timer_ClearIR(IR_TIMER);
	PIN_SEL0 &= ~(0x3 << 8); //set pin as GPIO

	int time = timer_GetCR(IR_TIMER, IR_CAPTURE);
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

	}
}

void EINT3_IRQHandler(void){
	timer_Reset(IR_TIMER);
	GPIO_Int_Clear(IR_IOPORT, 1 << IR_PIN);
	PIN_SEL0 |= 0x3 << 8;	//set pin as capture pin

}
