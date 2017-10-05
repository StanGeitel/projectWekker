
#ifndef IR_H_
#define IR_H_

#define SIRC_LENGTH			12
#define MAX_TIME_BIT0		700
#define MIN_TIME_BIT0		500
#define MAX_TIME_BIT1		1300
#define MIN_TIME_BIT1		1100
#define MAX_TIME_STARTBIT	2500
#define MIN_TIME_STARTBIT	2300

#define IR_TIMER	TIMER2
#define IR_CAPTURE	CAP0
#define IR_IOPORT	PORT0
#define IR_PIN		4

#define button1 			0x00
#define button2 			0x00
#define button3 			0x00
#define button4 			0x00
#define button5				0x00
#define button6			 	0x00
#define button7 			0x00
#define button8 			0x00
#define button9 			0x00
#define button0 			0x00
#define buttonVolumeUp 		0x00
#define buttonVolumeDown 	0x00
#define statusAlarm 		0x00

void IR_Init(void);
void IR_IRQ(void);
void setButton(char button);

#endif
