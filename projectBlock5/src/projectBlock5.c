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

#include <stdio.h>
#include "LPC1769.h"
<<<<<<< HEAD
#include "IR.h"
int test = 0;
=======
#include "timer.h"
#include "display.h"
>>>>>>> d629ec280d73f88b832938ccc0e336e29ced9f4d

int main(void) {
	//PIN_SEL0 |= 0x30F; //select pin sda1 (P0.0) and scl1 (P0.1) and CAP2.0 (P0.4)
	PIN_SEL0 |= 0x300; //select pin
	PIN_SEL0 |= 1 << 31;
	PIN_SEL1 |= 1 << 5;
	PIN_SEL4 |= 1 << 2;

<<<<<<< HEAD

	IR_Init();
=======
>>>>>>> d629ec280d73f88b832938ccc0e336e29ced9f4d
	while(1);
}



