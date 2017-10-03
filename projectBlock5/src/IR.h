
#ifndef IR_H_
#define IR_H_

#define SIRC_LENGTH			12
#define MAX_TIME_BIT0		700
#define MIN_TIME_BIT0		500
#define MAX_TIME_BIT1		1300
#define MIN_TIME_BIT1		1100
#define MAX_TIME_STARTBIT	2500
#define MIN_TIME_STARTBIT	2300

#define TIMER	TIMER0
#define PORT	PORT0
#define PIN		0

void IR_Init(void);
void IR_IRQ(void);

#endif