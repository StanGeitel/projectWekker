/*
 * alarm.h
 *
 *  Created on: 23 Sep 2017
 *      Author: stan
 */

#ifndef ALARM_H_
#define ALARM_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LPC1769.h"
#include "RealTimeClock.h"
#include "display.h"

void alarmInit(void);
void writeTimeToDisplay(void);
void writeProblemToDisplay(int a, char op, int b);
void solveProblem(void);
void sum(void);
void subtract(void);
void multiply(void);
void divide(void);
int getRandom(int max);

#endif /* ALARM_H_ */
