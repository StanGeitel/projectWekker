
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

Problem problem;
char userAnswer[5] = {'=',' ',' ',' ',' '};
char alarmTime[5] = {'1','6',':','3','7'};
unsigned char amplifier = 1, posAlarmTime = 0, posUserAnswer = 4;
bool settingAlarmTime = false, alarmOn = false, alarmActive = false;

void alarm_Init(void){
	system_Init();
	display_Init();
	sound_Init();
	calculator_Init();
	RTC_Init(0, 45, 20);
	IR_Init();
}

void alarm_TurnOn(void){
	alarmOn = true;
	sound_Select(&sineWave, 1);
	sound_Play();
	gen_Problem();
	display_Set(problem.arr);
	display_Write();
}

void alarm_TurnOff(void){
	alarmOn = false;
	sound_Pauze();
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
		posAlarmTime == 3 ? posAlarmTime == 3 : posAlarmTime++;
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
		alarm_setTime(RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register)), RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Hours_Register)));
	}
	else{
		display_Set("XXXXX");
		display_Write();
		for(int i =0; i < 5000; i++){
			asm("nop");
		}
		display_Set(problem.arr);
		display_Write();
		sound_SetAmplefier(amplifier++);
	}
	posUserAnswer = 4;
	for(int i = 0; i < 5; i++){
		userAnswer[i] = ' ';
	}
}

void alarm_SetButton(char button){
	if(alarmOn){
		if(button <= 9){
			alarm_SetUserAnswer(button + 49);
		}
		else{
			switch(button){
			case buttonOk:			alarm_CheckUserAnswer();
				break;
			case buttonUp:			alarm_MoveLeft();
				break;
			case buttonDown:		alarm_MoveRight();
				break;
			}
		}
	}
	else if(settingAlarmTime){
		if(button <= 9){
			alarm_SetAlarmTime(button + 1);
		}
		else{
			switch(button){
			case setAlarm:
			case buttonOk:
			{settingAlarmTime = false; posAlarmTime = 0; alarm_setTime(RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register)), RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Hours_Register)));}
				break;
			case buttonUp:		alarm_MoveLeft();
				break;
			case buttonDown:	alarm_MoveRight();
				break;
			}
		}
	}
	else{
		switch(button){
		case setAlarm:
		{settingAlarmTime = true; display_Set(alarmTime); display_Write();}
			break;
		case buttonVolumeDown:		sound_SetAmplefier(amplifier--);
			break;
		case buttonVolumeUp:		sound_SetAmplefier(amplifier++);
			break;
		case setActive:				alarm_ToggleActive();
			break;
		}
	}
}

void alarm_setTime(int min, int hour){
	char RTC_time[5] =  {'0','0',':','0','0'};
    RTC_time[0] = (char)(hour/10) + '0';
    RTC_time[1] = (char)(hour%10) + '0';
    RTC_time[2] = ':';
    RTC_time[3] = (char)(min/10) + '0';
    RTC_time[4] = (char)(min%10) + '0';

   	display_Set(RTC_time);
   	display_Write();

	int check = 1;
	for(int i = 0 ; i < 5 ; i++){
		if(!(alarmTime[i] == RTC_time[i])){
			check = 0;
		}
	}
	if(check == 1){
		printf("Alarm aan \n");
		alarm_TurnOn();
	}
}

void alarm_setAlarmTime(void){
	for(int i = 0; i < 5; i++){
		char dataRegister = RTC_Status_Register + i;
		RTC_WriteData(RTC_SlaveAddress, dataRegister, alarmTime[i]);
	}
}

void alarm_getAlarmTime(void){
	for(int i = 0; i < 5; i++){
		char dataRegister = RTC_Status_Register + i;
		alarmTime[i] = RTC_ReadData(RTC_SlaveAddress, dataRegister);
	}
	printf("don \n");
}

