/*
 * alarm.c
 *
 *  Created on: 23 Sep 2017
 *      Author: stan
 */

#include "alarm.h"

void alarmInit(void){
	I2C_Init();
	RTC_Init();
	displayInit();

	//init counter for seconds
	writeTimeToDisplay();
	srand(time(NULL));
}

void writeTimeToDisplay(void){
	char time[5];
	time[0] = (char)RTC_GetMinutes() % 10;
	time[1] = (char)RTC_GetMinutes() / 10;
	time[2] = ':';
	time[3] = (char)RTC_GetHours() % 10;
	time[4] = (char)RTC_GetHours() / 10;
	setMessage(time);
}

//IRHandler for time

//IRHandler for alarm

//PWM for audiosignals???

void writeProblemToDisplay(int a, char operator, int b){
	char problem[5];
	problem[0] = (char)(b % 10);
	problem[1] = (char)(b / 10);
	problem[2] = operator;
	problem[3] = (char)(a % 10);
	problem[4] = (char)(a / 10);
	setMessage(problem);
}

void solveProblem(void) {
	int a = getRandom(3);
	switch (a) {
	case 0: sum();
			break;
	case 1: subtract();
			break;
	case 2: multiply();
			break;
	case 3: divide();
			break;
	}
}

void sum(void){
	int a = getRandom(99);
	int b = getRandom(99);
	int c = a + b;
	int d;
	writeProblemToDisplay(a, '+', b);
	do {
		scanf("%d", &d); //get an answer via remote
		if (d != c) {
			//volumeUp();
		}
	} while (d != c);
}

void subtract(void) {
	int a = getRandom(99);
	int b = getRandom(99);
	int c = a - b;
	int d;
	writeProblemToDisplay(a, '-', b);
	do {
		scanf("%d", &d);  //get an answer via remote
		if (d != c) {
			//volumeUp();
		}
	} while (d != c);
}
void multiply(void) {
	int a = getRandom(99);
	int b = getRandom(99);
	int c = a * b;
	int d;
	writeProblemToDisplay(a, 'x', b);
	do {
		scanf("%d", &d);  //get an answer via remote
		if (d != c) {
			//volumeUp();
		}
	} while (d != c);
}

void divide(void) {
	int a = getRandom(99);
	int b = getRandom(99);
	int c = a / b;
	int d;
	writeProblemToDisplay(a, '%', b);
	do {
		scanf("%d", &d);  //get an answer via remote
		if (d != c) {
			//volumeUp();
		}
	} while (d != c);
}

int getRandom(int max) {
	int r = rand() % (max + 1);
	return r;
}
