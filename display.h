/*
 * display.h
 *
 *  Created on: 19 Sep 2017
 *      Author: stan
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "LPC1769.h"
#include <string.h>

//add correct gpio pins	 	pins on shift register
#define FIO2DIR		(*(unsigned int *) 0x2009C040)
#define FIO2MASK	(*(unsigned int *) 0x2009C050)
#define FIO2PIN		(*(unsigned int *) 0x2009C054)
#define FIO2SET		(*(unsigned int *) 0x2009C058)
#define FIO2CLR		(*(unsigned int *) 0x2009C05C)

#define SHCLK 		(0x1)			//shift register clock
#define STCLK 		(0x1 << 1)		//storage register clock
#define SHMR		(0x1 << 2)		//shift register master reset LOW-active
#define SHDI 		(0x1 << 3)		//shift register data input
#define RCCLK		(0x1 << 4)		//clock of ripple counter
#define RCRS		(0x1 << 5)		//Reset of ripple counter

static unsigned int buffer1[7];
static unsigned int buffer2[7];
static unsigned int (*pReadBuffer)[7];
static unsigned int (*pWriteBuffer)[7];

void displayInit(void);
void setMessage(char message[5]);
void setCharacter(char c, int pos);
void writeToDisplay(void);
void writeDataToShift(int row);
void writeDataToStorage(void);
void turnOnRow(int row);
void upRippleCounter(void);
void resetRippleCounter(void);
void clearDisplay(void);
void clearRows(void);
void clearCharacter(int pos);
void swapBuffer(void);
void test1(void);

#endif /* DISPLAY_H_ */
