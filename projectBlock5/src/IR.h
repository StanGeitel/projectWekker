
#ifndef IR_H_
#define IR_H_

#define SIRC_LENGTH			11
#define MAX_TIME_BIT0		700
#define MIN_TIME_BIT0		500
#define MAX_TIME_BIT1		1300
#define MIN_TIME_BIT1		1100
#define MAX_TIME_STARTBIT	2500
#define MIN_TIME_STARTBIT	2300
#define IR_ADDRESS 			12

#define IR_TIMER	TIMER2
#define IR_CAPTURE	CAP0
#define IR_IOPORT	PORT0
#define IR_PIN		4

void IR_Init(void);
void IR_IRQ(void);

#endif
