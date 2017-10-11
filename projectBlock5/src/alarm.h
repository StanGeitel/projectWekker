/*
 * alarm.h
 *
 *  Created on: 23 Sep 2017
 *      Author: stan
 */

#ifndef ALARM_H_
#define ALARM_H_

#define BUTTON_POWER		21

#define BUTTON_UP			13	//next pos
#define BUTTON_DOWN			22	//prev pos

#define BUTTON_VOLUMEUP 	18  //vol+
#define BUTTON_VOLUMEDOWN 	19 //vol-

#define BUTTON_PLAY			23	//ok knop
#define BUTTON_PAUZE		63	//edit time
#define BUTTON_STOP			37	//edit alarm
#define BUTTON_MUTE			20	//enable disable alarm

typedef struct{
	unsigned char minutes;
	unsigned char hours;
}time;

void alarm_Init(void);
void alarm_print(unsigned char min, unsigned char hour);
void alarm_TurnOn(void);
void alarm_TurnOff(void);
void alarm_MoveLeft(void);
void alarm_MoveRight(void);
void alarm_SetAlarmTime(char number);
void alarm_ToggleActive(void);
void alarm_SetUserAnswer(char button);
void alarm_CheckUserAnswer(void);
void alarm_SetButton(unsigned char button);
void alarm_SetTime(time *Time, unsigned char button);
void alarm_setAlarmTime(void);
void alarm_getAlarmTime(void);

#endif /* ALARM_H_ */
