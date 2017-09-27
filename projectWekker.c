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
	char arr[5] = {'0','1',':','3','4'};
	setMessage(arr);
    while(1) {
    	upRippleCounter();
    }
    return 0 ;
}
