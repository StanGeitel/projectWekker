/*
 * alarm.h
 *
 *  Created on: 23 Sep 2017
 *      Author: stan
 */

#ifndef ALARM_H_
#define ALARM_H_

#define button1 			0
#define button2 			1
#define button3 			2
#define button4 			3
#define button5				4
#define button6			 	5
#define button7 			6
#define button8 			7
#define button9 			8
#define buttonLeft			9	//nee toch niet
#define buttonRight			10	//ook niet
#define buttonEnter			11	//ook niet
#define buttonVolumeUp 		36  //vol+
#define buttonVolumeDown 	100 //vol-
#define statusAlarm 		24	//11 1-

void alarm_Init(void);
void alarm_On(void);
void check_User_Answer(void);
void alarm_Off(void);
void down_Volume(void);
void up_Volume(void);
void set_Alarm_Time(char number);
char* get_Alarm_Time(void);
void setButton(char button);
void move_Left(void);
void move_Right(void);
void set_User_Answer(char button);

#endif /* ALARM_H_ */
