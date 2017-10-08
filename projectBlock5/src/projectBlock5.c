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

#include <cr_section_macros.h>
#include "LPC1769.h"
#include "display.h"
#include "RealTimeClock.h"
#include "alarm.h"

int main(void) {
	system_Init();
	display_Init();
//	sound_Init();
//	RTC_Init(0, 10, 10);
	alarm_Init();
	alarm_TurnOn();
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
