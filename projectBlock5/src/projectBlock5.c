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
#include "IR.h"
#include <cr_section_macros.h>
#include "LPC1769.h"
#include "display.h"
#include "RealTimeClock.h"
#include "alarm.h"

int main(void) {
	system_Init();
	display_Init();
	alarm_Init();
	alarm_TurnOn();
	alarm_SetButton(4);
	alarm_SetButton(10);
	alarm_SetButton(11);
	alarm_SetButton(9);
	alarm_SetButton(11);
	alarm_SetButton(1);
	alarm_SetButton(11);
	alarm_SetButton(5);
	alarm_SetButton(11);
	alarm_SetButton(3);
	alarm_SetButton(12);
	alarm_SetButton();

//	alarm_TurnOn();
//	alarm_VolumeUp();
//	alarm_VolumeDown();
//	alarm_SetButton(setAlarm);
//	alarm_SetButton(button4);
//	alarm_MoveLeft();
//	alarm_MoveRight();
//	alarm_SetButton(button7);
//	alarm_SetButton(setAlarm);
//	alarm_ToggleActive();
//	alarm_CheckUserAnswer();

	while(1);
	return(0);
}
