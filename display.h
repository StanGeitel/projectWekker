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
#define GPIO		0
#define SHCLK 		0		//11 shift register clock
#define STCLK 		1		//12 storage register clock
#define SHMR		2		//10 shift register master reset LOW-active
#define SHDI 		3		//14 shift register data input
#define RCCLK		4		//clock of ripple counter
#define RCRS		5		//Reset of ripple counter

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
void writeGpio(int pin, int state);
void swapBuffer(void);

#endif /* DISPLAY_H_ */
