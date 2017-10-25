#include <stdbool.h>
#include <string.h>
#include "alarm.h"
#include "GPIO.h"
#include "LPC1769.h"
#include "display.h"
#include "calculator.h"
#include "RealTimeClock.h"
#include "sound.h"
#include "timer.h"

#define ALARM_IOPORT	2
#define LED_PIN			5

bool alarmActive = false;
char screenMenu = 0; //001 is time, 010 time aanpassen, 100 alarm aanpassen
char alarmTime[5] = {'0','0',':','0','0'};
char rtcTime[5] = {'0','0',':','0','0'};
char userAwnser[6] = {' ',' ',' ',' ',' ', '\0'};
char temp[5] =  {'0','0',':','0','0'};
char userAwnserCursor = 0;
char cursorPosition = 0;
char amplifier = 1;

time timeBuffer;
time alarmBuffer;

void alarm_Init(void){
	display_Init();
	sound_Init();
	calculator_Init();
	IR_Init();

	GPIO_SetDIR(ALARM_IOPORT, (0x1C | 1 << LED_PIN));
	GPIO_Clear(ALARM_IOPORT, 1 << LED_PIN);
	sound_Select(&totalySpies, 1, FALSE);
	sound_Play();
	alarmBuffer.minutes = 22;
	I2C_Init();
	RTC_Init(0, 0, 0);
}

void alarm_SetButton(char button){ //write alarm to rtc moet nog
	if(button == BUTTON0){
		button = -1;
	}

	if(alarmActive){
		if(button < 9){
			printf("Button ingedrukt antwoord \n");
			userAwnser[userAwnserCursor] = button + 48 + 1;
			userAwnserCursor++;
			writeWordToDisplay(userAwnser);
		}else if(button == BUTTONOK){
			if(strcmp(userAwnser, getProblemAwnser()) == 0){ //correct awnser
				printf("User awnser correct! \n");
				writeWordToDisplay("Nice!");
				alarm_TurnOff();
			}else{ //incorrect awnser
				printf("User awnser incorrect! \n");
				writeWordToDisplay("Wrong");
				clearUserAwnser();
				userAwnserCursor = 0;
				printf("Amplifier: %d \n", amplifier);
				sound_SetAmplefier(amplifier);
				amplifier++;
				//sound_IncreaseVolume();
			}
		}else if(button == SET_PROBLEM_SCREEN){
			writeWordToDisplay(getProblemArr());
		}
	}else{
		if(button == MENU_TIME){
			screenMenu = 1;
			setTimeBufferByRTC(&timeBuffer);
			writeWordToDisplay(convertTimeToArr(timeBuffer.minutes, timeBuffer.hours));

		}else if(button == MENU_TIMECHANGE){
			screenMenu = 2;
			setTimeBufferByRTC(&timeBuffer);
			writeWordToDisplay(convertTimeAndCursorToArr(timeBuffer.minutes, timeBuffer.hours, cursorPosition));

		}else if(button == MENU_ALARMCHANGE){
			screenMenu = 4;
			setTimeBufferByArr(&alarmBuffer, alarmTime);
			writeWordToDisplay(convertTimeAndCursorToArr(alarmBuffer.minutes, alarmBuffer.hours, cursorPosition));
		}

		if(screenMenu == 2){ //edit time
			if(button < 9){
				rtcTime[cursorPosition] = button + 48 + 1;
				setTimeBufferByArr(&timeBuffer, rtcTime);

				if(timeBuffer.hours > 23){
					timeBuffer.hours = 23;
				}
				if(timeBuffer.minutes > 59){
					timeBuffer.minutes = 59;
				}

				writeWordToDisplay(convertTimeToArr(timeBuffer.minutes, timeBuffer.hours));
			}else if(button == BUTTONOK){
				screenMenu = 1;
				writeWordToDisplay("Saved");
				RTC_WriteData(RTC_SlaveAddress, RTC_Minuten_Register, RTC_decToBcd(timeBuffer.minutes));
				RTC_WriteData(RTC_SlaveAddress, RTC_Hours_Register, RTC_decToBcd(timeBuffer.hours));
				T_TC(TIMER3) = 0;
			}


		}else if(screenMenu == 4){ //edit alarm
			if(button < 9){
				alarmTime[cursorPosition] = button + 48 + 1;
				setTimeBufferByArr(&alarmBuffer, alarmTime);

				if(alarmBuffer.hours > 23){
					alarmBuffer.hours = 23;
				}
				if(alarmBuffer.minutes > 59){
					alarmBuffer.minutes = 59;
				}

				writeWordToDisplay(convertTimeToArr(alarmBuffer.minutes, alarmBuffer.hours));
			}else if(button == BUTTONOK){
				screenMenu = 1;
				writeWordToDisplay("Saved");
				RTC_WriteData(RTC_SlaveAddress, RTC_AlarmMinutes_Register, RTC_decToBcd(alarmBuffer.minutes));
				RTC_WriteData(RTC_SlaveAddress, RTC_AlarmHours_Register, RTC_decToBcd(alarmBuffer.hours));
				T_TC(TIMER3) = 0;
			}
		}

		if(button == BUTTONLEFT && screenMenu != 1){
			cursor_MoveLeft();
			(screenMenu == 4) ? (writeWordToDisplay(convertTimeAndCursorToArr(alarmBuffer.minutes, alarmBuffer.hours, cursorPosition))) :(writeWordToDisplay(convertTimeAndCursorToArr(timeBuffer.minutes, timeBuffer.hours, cursorPosition)));
		}else if(button == BUTTONRIGHT && screenMenu != 1){
			cursor_MoveRight();
			(screenMenu == 4) ? (writeWordToDisplay(convertTimeAndCursorToArr(alarmBuffer.minutes, alarmBuffer.hours, cursorPosition))) :(writeWordToDisplay(convertTimeAndCursorToArr(timeBuffer.minutes, timeBuffer.hours, cursorPosition)));
		}
	}
}

void cursor_MoveLeft(void){
	if(cursorPosition == 3){
		cursorPosition = 1;
	}else{
		cursorPosition == 0 ? cursorPosition == 0 : cursorPosition--;
	}
}

void cursor_MoveRight(void){
	if(cursorPosition == 1){
		cursorPosition = 3;
	}else{
		cursorPosition == 4 ? cursorPosition == 4 : cursorPosition++;
	}
}
char* convertTimeToArr(int min, int hour){
	//char temp[5] =  {'0','0',':','0','0'};

	temp[0] = (char)(hour/10) + '0';
	temp[1] = (char)(hour%10) + '0';
	temp[2] = ':';
	temp[3] = (char)(min/10) + '0';
	temp[4] = (char)(min%10) + '0';
	return temp;
}

char* convertTimeAndCursorToArr(int min, int hour, int position){
	temp[0] = (char)(hour/10) + '0';
	temp[1] = (char)(hour%10) + '0';
	temp[2] = ':';
	temp[3] = (char)(min/10) + '0';
	temp[4] = (char)(min%10) + '0';
	temp[position] = '-';
	return temp;
}

void writeWordToDisplay(char* string){
	display_Set(string);
	display_Write();
}

void setTimeBufferByRTC(time *buffer){
	(*buffer).minutes = RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register));
	(*buffer).hours = RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Hours_Register));
}

void setTimeBufferByArr(time *buffer, char arr[]){
	(*buffer).minutes = ((arr[3] - 48) * 10) + (arr[4] - 48);
	(*buffer).hours = ((arr[0] - 48) * 10) + (arr[1] - 48);
}

void clearUserAwnser(){
	userAwnser[0] = ' ';
	userAwnser[1] = ' ';
	userAwnser[2] = ' ';
	userAwnser[3] = ' ';
	userAwnser[4] = ' ';
	userAwnser[5] = '\0';
}

void alarm_TurnOn(void){
	printf("Alarm active! \n");
	GPIO_Set(ALARM_IOPORT, 1 << LED_PIN);

	alarmActive = true;
	userAwnserCursor = 0;
	clearUserAwnser();
	gen_Problem();
	writeWordToDisplay(getProblemArr());
	sound_Select(&airRaid, 2, 1);
	sound_Play();

}

void alarm_TurnOff(void){
	alarmActive = false;
	GPIO_Clear(ALARM_IOPORT, 1 << LED_PIN);
	amplifier = 1;
	sound_Stop();
	sound_Select(&powerOff,1, FALSE);
	sound_Play();
}

void TIMER3_IRQHandler(void){
	timer_ClearIR(TIMER3);
	char *a;
	printf("TIMER3_IRQHandler \n");
	int rtcMinuten = RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register));
	int rtcUren = RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Hours_Register));

	if(rtcMinuten == alarmBuffer.minutes && rtcUren == alarmBuffer.hours){
		alarm_TurnOn();
	}else if(!alarmActive && screenMenu != 2 && screenMenu != 4){ //don't write time if alarm,  time- or alarm change is going
		a = convertTimeToArr(rtcMinuten, rtcUren);
		writeWordToDisplay(a);
	}
}
