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
    while(1) {

    }
    return 0 ;
}
