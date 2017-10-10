/*
 * alarm.h
 *
 *  Created on: 23 Sep 2017
 *      Author: stan
 */

#ifndef ALARM_H_
#define ALARM_H_

#define button0				10	//10
#define buttonUp			10	//nee toch niet
#define buttonDown			11	//ook niet
#define buttonOk			12	//ook niet
#define buttonVolumeUp 		37  //vol+
#define buttonVolumeDown 	101 //vol-
#define setAlarm 			25	//11 1-
#define setActive			26	//12

void alarm_Init(void);
void alarm_TurnOn(void);
void alarm_TurnOff(void);
void alarm_MoveLeft(void);
void alarm_MoveRight(void);
void alarm_SetAlarmTime(char number);
void alarm_ToggleActive(void);
void alarm_SetUserAnswer(char button);
void alarm_CheckUserAnswer(void);
void alarm_SetButton(char button);
void alarm_setTime(int min, int hour);
void alarm_setAlarmTime(void);
void alarm_getAlarmTime(void);

#endif /* ALARM_H_ */
