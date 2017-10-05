/*
 * alarm.h
 *
 *  Created on: 23 Sep 2017
 *      Author: stan
 */

#ifndef ALARM_H_
#define ALARM_H_

#include "LPC1769.h"
#include "display.h"
#include "calculator.h"

void alarm_Init(void);
void alarm_On(void);
void alarm_Off(void);
void up_Volume(void);
void down_Volume(void);
char* get_Alarm_Time(voi);

#endif /* ALARM_H_ */
