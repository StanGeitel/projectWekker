#include "LPC1769.h"
#include "timer.h"
#include "GPIO.h"
#include "IR.h"
#include "alarm.h"
#include "RealTimeClock.h"
#include "display.h"

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
		printf("data: %d \n", data);
		data = (data & ~0x1F) >> 5;
		setButton(data);
	}
}

void EINT3_IRQHandler(void){
	timer_Reset(IR_TIMER);
	GPIO_Int_Clear(IR_IOPORT, 1 << IR_PIN);
	PIN_SEL0 |= 0x3 << 8;	//set pin as capture pin
}

void setButton(char button){
	switch(button){
	case statusAlarm:
		display_Set(get_Alarm_Time());
		display_Write();

		/*delay*/
		for(int i = 0 ; i < 100000 ; i++){
			asm("nop");
		}

		display_Set(RTC_getTime());
		display_Write();
		break;
	case buttonVolumeUp:
		upVolume();
		break;
	case buttonVolumeDown:
		downVolume();
		break;
	case button1:
		break;
	case button2:
		break;
	case button3:
		break;
	case button4:
		break;
	case button5:
		break;
	case button6:
		break;
	case button7:
		break;
	case button8:
		break;
	case button9:
		break;
	default:
		break;
	}
}
