#include "LPC1769.h"
#include "timer.h"
#include "GPIO.h"
#include "IR.h"

short data = 0;
unsigned char bit = 0;

void IR_Init(void){
	timer_Init(IR_TIMER,3999);
	timer_SetMR(IR_TIMER,MR0,MIN_TIME_BIT0);
	timer_SetMCR(IR_TIMER,MR0,1);
}

void IR_IRQ(void){
	if((GPIO_Int_StatusR(IR_IOPORT) & IR_PIN)){	//if pin is rising edge sensitive
		short time = timer_GetCount(IR_TIMER);
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
		GPIO_Int_DisableR(IR_IOPORT,IR_PIN);
		GPIO_Int_DisableF(IR_IOPORT,IR_PIN);
	}else{
		timer_Reset(IR_TIMER);
	}
	GPIO_Int_Clear(IR_IOPORT, IR_PIN);
}

void IR_TIMER0_IRQHandler(void){
	GPIO_Int_EnableR(IR_TIMER,IR_PIN);
	GPIO_Int_EnableF(IR_TIMER,IR_PIN);
	timer_ClearIR(IR_TIMER);
}
