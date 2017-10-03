
#ifndef DISPLAY_H_
#define DISPLAY_H_

#define DISPLAY_TIMER	TIMER1
#define DISPLAY_IOPORT	PORT0
#define HIGH 	1
#define LOW		0
#define H_STO	1 << 16
#define H_RST(x)	{x ? GPIO_Set(PORT0,1 << 17) : GPIO_Clear(PORT0,1 << 17);}
#define V_CLK(x)	{x ? GPIO_Set(PORT0,1 << 1) : GPIO_Clear(PORT0,1 << 1);}
#define V_RST(x)	{x ? GPIO_Set(PORT0,1 << 0) : GPIO_Clear(PORT0,1 << 0);}
#define PRESCALER	6666

void display_Init(void);
void display_Set(char message[5]);
void display_SetChar(char c, unsigned char pos);
void display_Write(void);

#endif
