/*
 * alarm.h
 *
 *  Created on: 23 Sep 2017
 *      Author: stan
 */

#ifndef ALARM_H_
#define ALARM_H_

#define BUTTONOK 			23 //play
#define BUTTONLEFT 			17
#define BUTTONRIGHT			16
#define MENU_TIME			9 //10
#define MENU_TIMECHANGE		12 //11
#define MENU_ALARMCHANGE	13 //12
#define SET_PROBLEM_SCREEN	27 //GROEN


typedef struct{
	unsigned char minutes;
	unsigned char hours;
}time;


void alarm_Init(void);
void alarm_VolumeDown(void);
void alarm_VolumeUp(void);
void alarm_SetButton(char button);
void clearUserAwnser();
void setTimeBufferByRTC(time *buffer);
void setTimeBufferByArr(time *buffer, char arr[]);

void writeWordToDisplay(char* string);
char* convertTimeToArr(int min, int hour);
char* convertTimeAndCursorToArr(int min, int hour, int position);

void cursor_MoveRight(void);
void cursor_MoveLeft(void);

#endif /* ALARM_H_ */
