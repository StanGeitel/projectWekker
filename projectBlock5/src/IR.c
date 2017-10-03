#include "LPC1769.h"
#include "timer.h"
#include "GPIO.h"
#include "IR.h"

short data = 0;
unsigned char bit = 0;

void IR_Init(void){
	timer_Init(TIMER,3999);
	timer_SetMR(TIMER,MR0,MIN_TIME_BIT0);
	timer_SetMCR(TIMER,MR0,1);
}

void IR_IRQ(void){
	if((GPIO_Int_StatusR(PORT) & PIN)){	//if pin is rising edge sensitive
		short time = timer_GetCount(TIMER);
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
		timer_Reset(TIMER);
		GPIO_Int_DisableR(PORT,PIN);
		GPIO_Int_DisableF(PORT,PIN);
	}else{
		timer_Reset(TIMER);
	}
	GPIO_Int_Clear(PORT, PIN);
}

void TIMER0_IRQHandler(void){
	GPIO_Int_EnableR(TIMER,PIN);
	GPIO_Int_EnableF(TIMER,PIN);
	timer_ClearIR(TIMER);
}
