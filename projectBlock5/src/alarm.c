
#include <stdbool.h>
#include <string.h>
#include "alarm.h"
#include "GPIO.h"
#include "LPC1769.h"
#include "display.h"
#include "calculator.h"
#include "RealTimeClock.h"
//#include "soundFiles.h"
#include "sound.h"

Problem problem;

char alarmTime[5] = {'1','0',':','2','6'};
char userAnswer[5] = {' ',' ',' ',' ',' '};
unsigned char volume = 1, posAlarmTime = 0, posUserAnswer = 4;
bool settingAlarmTime = false, alarmOn = false, alarmActive = false;

void alarm_Init(void){
	system_Init();
	display_Init();
	alarm_Init();
	//sound_Init();
	calculator_Init();
	RTC_Init(0, 30, 10);
	RTC_setAlarmTime();
}

void alarm_TurnOn(void){
	alarmOn = true;
	//sound_Select(&sineWave, 1);
	//sound_Play();
	gen_Problem();
	display_Set(problem.arr);
	display_Write();
	GPIO_Clear(2, (0x1 << (volume + 1)));
}

void alarm_TurnOff(void){
	alarmOn = false;
	sound_Pauze();
	volume = 1;
	GPIO_Set(2, (0x07 << 2));
}

void alarm_VolumeDown(void){
	volume == 1 ? volume == 1 : volume--;
	GPIO_Set(2, (0x07 << 2));
	GPIO_Clear(2, (0x1 << (volume + 1)));
}

void alarm_VolumeUp(void){
	volume == 3 ? volume == 3 : volume++;
	GPIO_Set(2, (0x07 << 2));
	GPIO_Clear(2, (0x1 << (volume + 1)));
}

void alarm_MoveLeft(void){
	if(alarmOn){
		posUserAnswer == 1 ? posUserAnswer == 1 : posUserAnswer--;
	}
	if(settingAlarmTime){
		posAlarmTime == 0 ? posAlarmTime == 0 : posAlarmTime--;
	}
}

void alarm_MoveRight(void){
	if(alarmOn){
		posUserAnswer == 4 ? posUserAnswer == 4 : posUserAnswer++;
	}
	if(settingAlarmTime){
		posAlarmTime == 4 ? posAlarmTime == 4 : posAlarmTime++;
	}
}

void alarm_SetAlarmTime(char number){
	if(posAlarmTime > 1){
		alarmTime[posAlarmTime + 1] = number;
	}
	else if(posAlarmTime <= 1){
		alarmTime[posAlarmTime] = number;
	}
	display_Set(alarmTime);
	display_Write();
}

void alarm_ToggleActive(void){
	alarmActive = ~alarmActive;
}

void alarm_SetUserAnswer(char button){
	userAnswer[posUserAnswer] = button;
	display_Set(userAnswer);
	display_Write();
}

void alarm_CheckUserAnswer(void){
	if(strcmp(userAnswer, problem.answer) == 0){
		alarm_TurnOff();
		display_Set(RTC_getTime());
		display_Write();
	}
	else{
		display_Set("XXXXX");
		display_Write();
		for(int i =0; i < 5000; i++){
			asm("nop");
		}
		display_Set(problem.arr);
		display_Write();
		alarm_VolumeUp();
	}
	posUserAnswer = 4;
	for(int i = 0; i < 5; i++){
		userAnswer[i] = ' ';
	}
}

void alarm_SetButton(char button){
	if(alarmOn){
		if(button <= 9){
			alarm_SetUserAnswer(button + 48);
		}
		else{
			switch(button){
			case buttonOk:			alarm_CheckUserAnswer();
				break;
			case buttonLeft:		alarm_MoveLeft();
				break;
			case buttonRight:		alarm_MoveRight();
				break;
			}
		}
	}
	else if(settingAlarmTime){
		if(button <= 9){
			alarm_SetAlarmTime(button + 48);
		}
		else{
			switch(button){
			case setAlarm:
			case buttonOk:
			{settingAlarmTime = false; posAlarmTime = 0; display_Set(RTC_getTime()); display_Write(); RTC_setAlarmTime();}
				break;
			case buttonLeft:		alarm_MoveLeft();
				break;
			case buttonRight:		alarm_MoveRight();
				break;
			}
		}
	}
	else{
		switch(button){
		case setAlarm:
		{settingAlarmTime = true; display_Set(alarmTime); display_Write();}
			break;
		case buttonVolumeDown:		alarm_VolumeDown();
			break;
		case buttonVolumeUp:		alarm_VolumeUp();
			break;
		case setActive:				alarm_ToggleActive();
			break;
		}
	}
}

void RTC_setTime(int min, int hour){
	char RTC_time[5] =  {'0','0',':','0','0'};
    RTC_time[0] = (char)(min/10) + '0';
    RTC_time[1] = (char)(min%10) + '0';
    RTC_time[2] = ':';
    RTC_time[3] = (char)(hour/10) + '0';
    RTC_time[4] = (char)(hour%10) + '0';

    display_Set(RTC_time);
    display_Write();

    RTC_getAlarmTime();

	if(strcmp(alarmTime, RTC_time) == 0){
		alarm_TurnOn();
	}
}

void RTC_setAlarmTime(void){
	for(int i = 0; i < 5; i++){
		char dataRegister = RTC_Status_Register + i;
		RTC_WriteData(RTC_SlaveAddress, dataRegister, alarmTime[i]);
	}
}

void RTC_getAlarmTime(void){
	for(int i = 0; i < 5; i++){
		char dataRegister = RTC_Status_Register + i;
		alarmTime[i] = RTC_ReadData(RTC_SlaveAddress, dataRegister);
	}
	printf("don \n");
}

//void alarm_WriteDisplay(bool setting){
//	if(setting){
//		display_Set(alarmTime);
//		display_Write();
//		for(int i = 0; i < 5000; i++){
//			asm("nop");
//		}
//		char alarm_Time[] = alarmTime;
//		alarm_Time[]
//		display_Set()
//	}

