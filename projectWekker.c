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
	displayInit();
    while(1) {
    	test1();
    	for(int i = 0; i < 100; i++){
    		asm("NOP");
    	}
    }
    return 0 ;
}
