/*
 * alarm.c
 *
 *  Created on: 23 Sep 2017
 *      Author: stan
 */

#include "alarm.h"

Problem problem;

void alarmInit(void){
	//I2C_Init();
	//RTC_Init();
	displayInit();
	calculatorInit();
	//init counter for seconds
	//setMessage(getTime());
}

//IRHandler for rtc 1HZ

//IRHandler for display writeToDisplay();

//IRHandler for alarm PWM for audiosignals???



void solveProblem(void){
	Problem* pProblem = &problem;
	setProblem(pProblem);
	setMessage(pProblem->arr);
	for(int i = 0; i <5; i++){
		printf("%c", pProblem->arr[i]);
	}
	int userAnswer;
	do {
		do{
			scanf("%d", &userAnswer); //get an answer via remote
		}while(!userAnswer);
		if (userAnswer != pProblem->answer) {
			//volumeUp();
		}
	} while ( userAnswer != pProblem->answer);
}

