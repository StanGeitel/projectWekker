/*
===============================================================================
 Name        : projectBlock5.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "LPC1769.h"
#include "display.h"
#include "sound.h"
#include <cr_section_macros.h>
#include <stdio.h>
#include "alarm.h"
#include "LPC1769.h"
#include "display.h"

int main(void) {
	alarm_Init();
	display_Init();
	RIT_COUNTER = 0;
	alarm_On();
	while(1);

}



