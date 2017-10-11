
#include <stdbool.h>
#include <string.h>
#include "alarm.h"
#include "GPIO.h"
#include "LPC1769.h"
#include "display.h"
#include "calculator.h"
#include "RealTimeClock.h"
#include "soundFiles.h"
#include "sound.h"
#include "IR.h"
#include "timer.h"

#define ALARM_IOPORT	2
#define LED_PIN			5

time timeBuffer;
time alarmBuffer;

Problem problem;

char userAnswer[5] = {'=',' ',' ',' ',' '};
unsigned char amplifier = 1;
unsigned char displayPos = 0;

bool editAlarm = false;
bool editTime = false;
bool alarmEnabled = false;
bool alarmOn = false;

void alarm_Init(void){
	display_Init();
	sound_Init();
	calculator_Init();
	RTC_Init();
	IR_Init();

	GPIO_SetDIR(ALARM_IOPORT, 1 << LED_PIN);
	sound_Select(&totalySpies, 1, FALSE);
	sound_Play();
}

void alarm_TurnOn(void){
	alarmOn = true;
	displayPos = 0;
	sound_Select(&airRaid, 2, TRUE);
	sound_Play();
	gen_Problem();
	display_Set(problem.arr);
	display_Write();
}

void alarm_TurnOff(void){
	alarmOn = false;
	sound_Stop();
	sound_Select(&powerOff,1,FALSE);
	sound_Play();
}

void alarm_MoveLeft(void){
	displayPos == 4 ? displayPos = 0 : displayPos++;
	if((editTime || editAlarm) && displayPos == 2){
		alarm_MoveLeft();
	}else if(alarmOn == 4){
		displayPos = 0;
	}
	display_SetCursor(displayPos);
}

void alarm_MoveRight(void){
	displayPos == 0 ? displayPos = 4 : displayPos--;
	if((editTime || editAlarm) && displayPos == 2){
		alarm_MoveRight();
	}else if(alarmOn == 4){
		displayPos = 3;
	}
	display_SetCursor(displayPos);
}

void alarm_SetTime(time *time, unsigned char button){
	button == 9 ? button = 0 : button++;

	switch(displayPos){
	case 0:
		time->minutes &= ~0xF;
		time->minutes |= button;
		break;
	case 1:
		time->minutes &= ~(0xF << 4);
		time->minutes |= button << 4;
		break;
	case 3:
		time->hours &= ~0xF;
		time->hours |= button;
		break;
	case 4:
		time->hours &= ~(0xF << 4);
		time->hours |= button << 4;
		break;
	}
	if(RTC_bcdToDec(time->minutes) > 60){
		time->minutes = 5 << 4 | 9;
	}
	if(RTC_bcdToDec(time->hours) > 24){
		time->hours = 2 << 4 | 3;
	}

	alarm_print(time->minutes,time->hours);
	alarm_MoveLeft();
}

void alarm_SetUserAnswer(char button){

}

void alarm_CheckUserAnswer(void){

}

void alarm_print(unsigned char min, unsigned char hour){
	char c[] = {
			((hour >> 4) & 0xF) + '0',
			(hour & 0xF) + '0',
			':',
			((min >> 4) & 0xF) + '0',
			(min & 0xF) + '0',
	};
	display_Set(c);
	display_Write();
}

void TIMER3_IRQHandler(void){
	timer_ClearIR(TIMER3);

	if(!alarmOn && !editAlarm && !editTime){
		timeBuffer.minutes = RTC_ReadData(RTC_Minuten_Register);
		timeBuffer.hours = RTC_ReadData(RTC_Hours_Register);
		alarmBuffer.minutes = RTC_ReadData(Alarm_Minuts_Register);
		alarmBuffer.hours = RTC_ReadData(Alarm_Hours_Register);
		if(timeBuffer.minutes == alarmBuffer.minutes && timeBuffer.hours == alarmBuffer.hours && alarmEnabled){
			alarm_TurnOn();
		}else{
			alarm_print(timeBuffer.minutes,timeBuffer.hours);
		}
	}
}

void alarm_SetButton(unsigned char button){
	switch(button){
	case BUTTON_UP:
		alarm_MoveLeft();
		break;
	case BUTTON_DOWN:
		alarm_MoveRight();
		break;
	case BUTTON_VOLUMEDOWN:
		sound_DecreaseVolume();
		break;
	case BUTTON_VOLUMEUP:
		sound_IncreaseVolume();
		break;
	default:

		if(alarmOn){
			if(button <= 9){
				alarm_SetUserAnswer(button);
			}else if(button == BUTTON_PLAY){
				alarm_CheckUserAnswer();
			}
		}else if(editTime){
			if(button <= 9){
				alarm_SetTime(&timeBuffer, button);
			}else if(button == BUTTON_PLAY){
				RTC_WriteData(RTC_Minuten_Register,timeBuffer.minutes);
				RTC_WriteData(RTC_Hours_Register,timeBuffer.hours);
				display_DisableCursor();
				editTime = false;
			}
		}else if(editAlarm){
			if(button <= 9){
				alarm_SetTime(&alarmBuffer, button);
			}else if(button == BUTTON_PLAY){
				RTC_WriteData(Alarm_Minuts_Register,alarmBuffer.minutes);
				RTC_WriteData(Alarm_Hours_Register,alarmBuffer.hours);
				timeBuffer.minutes = RTC_ReadData(RTC_Minuten_Register);
				timeBuffer.hours = RTC_ReadData(RTC_Hours_Register);

				alarm_print(timeBuffer.minutes,timeBuffer.hours);
				display_DisableCursor();
				editAlarm = false;
			}
		}else{
			switch(button){
			case BUTTON_PAUZE:
				editTime = true;
				timeBuffer.minutes = RTC_ReadData(RTC_Minuten_Register);
				timeBuffer.hours = RTC_ReadData(RTC_Hours_Register);
				displayPos = 0;
				display_SetCursor(displayPos);
				display_EnableCursor();
				break;
			case BUTTON_STOP:
				editAlarm = true;
				alarmBuffer.minutes = RTC_ReadData(Alarm_Minuts_Register);
				alarmBuffer.hours = RTC_ReadData(Alarm_Hours_Register);
				alarm_print(alarmBuffer.minutes,alarmBuffer.hours);
				displayPos = 0;
				display_SetCursor(displayPos);
				display_EnableCursor();
				break;
			case BUTTON_MUTE:
				alarmEnabled = !alarmEnabled;
				break;
			}
		}
		break;
	}
	(alarmEnabled && !editTime && !editAlarm) ? GPIO_Set(ALARM_IOPORT, 1 << LED_PIN) : GPIO_Clear(ALARM_IOPORT, 1 << LED_PIN);
}


