
#include "alarm.h"

Problem problem;
char alarmTime[5] = {'0','0',':','0','0'};
unsigned char vol = 0;

void alarmInit(void){
	calculatorInit();
	GPIO_Set(2, (0x07 << 2));
}

void alarmOn(void){
	Problem* pProblem = &problem;
	setProblem(pProblem);
	setMessage(pProblem->arr);
	upVolume();

	int userAnswer;
	do {
		do{
			scanf("%d", &userAnswer); //get an answer via remote
		}while(!userAnswer);
		if (userAnswer != pProblem->answer) {
			upVolume();
		}
	} while ( userAnswer != pProblem->answer);
}

void upVolume(void){
	vol++;
	GPIO_Set(2, (0x07 << 2));
	GPIO_Clear(2, (0x1 << (vol + 2)));
}



