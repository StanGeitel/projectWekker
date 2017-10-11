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
#include "sound.h"
#include "soundFiles.h"
#include "alarm.h"

int main(void) {
	system_Init();
	alarm_Init();
	while(1);
	return(0);
}
