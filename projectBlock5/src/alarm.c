
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

