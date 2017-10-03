/*
===============================================================================
 Name        : projectWekker.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "alarm.h"

int main(void) {
	alarmInit();
	Problem* pProblem = &problem;
	setProblem(pProblem);
	setMessage(pProblem->arr);
    while(1) {
    	writeToDisplay();
    }
    return 0 ;
}
