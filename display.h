/*
 * display.h
 *
 *  Created on: 19 Sep 2017
 *      Author: stan
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "LPC1769.h"

//add correct gpio pins	 	pins on shift register
#define GPIO		0
#define SHCLK 		0		//11 shift register clock
#define STCLK 		1		//12 storage register clock
#define SRMR		2		//10 shift register master reset LOW-active
#define SRD 		3		//14 shift register data input
#define RCCLK		4		//clock of ripple counter
#define RCRS		5		//Reset of ripple counter
#define DMEN		6		//JP1_2 is enable for demultiplexer

int buffer1[7];
int buffer2[7];
int (*pBuffer)[7];

void displayInit(void);
void writeMessage(char message[5]);
void setMessage(char message[5]);
void setCharacter(char c, int pos);
void writeToDisplay(void);
void writeDataToShift(int row);
void writeDataToStorage(void);
void turnOnRow(int row);
void upRippleCounter(void);
void resetRippleCounter(void);
void enableRow(void);
void disableRow(void);
void clearDisplay(void);
void clearCharacter(int pos);
void writeGpio(int pin, int state);

#endif /* DISPLAY_H_ */
