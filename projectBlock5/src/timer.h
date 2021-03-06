
#ifndef TIMER_H_
#define TIMER_H_

#define TIMER0	0
#define TIMER1	1
#define TIMER2	35
#define TIMER3	36
#define PWM		5
#define	MR0		0
#define	MR1		1
#define	MR2		2
#define	MR3		3
#define MR4		10
#define MR5		11
#define MR6		12
#define CR0		0
#define CR1		1
#define CR2		2
#define CR3		3
#define CAP0	0
#define CAP1 	1
#define RISING_EDGE		1
#define FALING_EDGE		2
#define BOTH_EDGES		3

void timer_Init(unsigned char timer, int prescaler);
void timer_ClearIR(unsigned char timer);
void timer_Enable(unsigned char timer);
void timer_Disable(unsigned char timer);
void timer_Reset(unsigned char timer);
void timer_SetPR(unsigned char timer, int prescaler);
void timer_SetMCR(unsigned char timer, unsigned char MR, unsigned char data);
void timer_SetMR(unsigned char timer, unsigned char MR, int count);
void timer_SetCTCR(unsigned char timer, unsigned char mode, unsigned char cap);
void timer_SetCCR(unsigned char timer, unsigned char cap, unsigned char data);
int timer_GetCR(unsigned char timer, unsigned char cap);
void timer_PWM_Enable(unsigned char channels);
void timer_PWM_SetMR(unsigned char MR, int count);
int timer_GetCount(unsigned char timer);

#endif /* TIMER_H_ */
