/*
 * timer.h
 *
 *  Created on: 28 Sep 2017
 *      Author: stan
 */

#ifndef TIMER_H_
#define TIMER_H_

#define TIMER0	0
#define TIMER1	1
#define TIMER2	23
#define TIMER3	24
#define	MR0		0
#define	MR1		1
#define	MR2		2
#define	MR3		3
#define M4		10
#define M5		11
#define M6		12
#define CR0		0
#define CR1		1
#define CR2		2
#define CR3		3

void timer_Init(unsigned char timer, int prescaler);
void timer_ClearIR(unsigned char timer);
void timer_Enable(unsigned char timer);
void timer_Disable(unsigned char timer);
void timer_Reset(unsigned char timer);
void timer_SetPR(unsigned char timer, int prescaler);
void timer_SetMCR(unsigned char timer, unsigned char MR, unsigned char data);
void timer_SetMR(unsigned char timer, unsigned char MR, short count);

#endif /* TIMER_H_ */
