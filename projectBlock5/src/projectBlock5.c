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

<<<<<<< HEAD
#include "LPC1769.h"

#include "display.h"
#include "sound.h"
=======
#include <cr_section_macros.h>

#include <stdio.h>
#include "alarm.h"
#include "LPC1769.h"
#include "display.h"
>>>>>>> 0797727b13ba934defffc04b08691aa6fce6326b

int main(void) {

<<<<<<< HEAD
<<<<<<< HEAD
	sound_Init(1);


=======
=======
	RIT_COUNTER = 0x0;

>>>>>>> 35cac88e1be13e7ff4577c5f5c863bdab4d2ab96
	alarm_Init();
	display_Init();
	alarm_On();
>>>>>>> 0797727b13ba934defffc04b08691aa6fce6326b
	while(1);

}



