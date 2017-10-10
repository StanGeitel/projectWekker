/*
 * alarm.h
 *
 *  Created on: 23 Sep 2017
 *      Author: stan
 */

#ifndef ALARM_H_
#define ALARM_H_

#define button0				24	//10
#define button1 			1
#define button2 			2
#define button3 			3
#define button4 			4
#define button5				5
#define button6			 	6
#define button7 			7
#define button8 			8
#define button9 			9
#define buttonLeft			10	//nee toch niet
#define buttonRight			11	//ook niet
#define buttonOk			12	//ook niet
#define buttonVolumeUp 		37  //vol+
#define buttonVolumeDown 	101 //vol-
#define setAlarm 			25	//11 1-
#define setActive			26	//12

void alarm_Init(void);
void alarm_TurnOn(void);
void alarm_TurnOff(void);
void alarm_VolumeDown(void);
void alarm_VolumeUp(void);
void alarm_MoveLeft(void);
void alarm_MoveRight(void);
void alarm_SetAlarmTime(char number);
void alarm_ToggleActive(void);
void alarm_SetUserAnswer(char button);
void alarm_CheckUserAnswer(void);
void alarm_SetButton(char button);
void RTC_setTime(int min, int hour);
void RTC_setAlarmTime(void);
void RTC_getAlarmTime(void);

#endif /* ALARM_H_ */
