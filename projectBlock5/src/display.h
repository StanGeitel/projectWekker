
#ifndef DISPLAY_H_
#define DISPLAY_H_

#define TIMER	TIMER1
#define PORT	PORT0
#define HIGH 	1
#define LOW		0

#define H_RST(x)	{x ? GPIO_Set(PORT,1 << 17) : GPIO_Clear(PORT,1 << 17);}
#define V_CLK(x)	{x ? GPIO_Set(PORT,1 << 1) : GPIO_Clear(PORT,1 << 1);}
#define V_RST(x)	{x ? GPIO_Set(PORT,1 << 0) : GPIO_Clear(PORT,1 << 0);}


void display_Init(void);
void display_Set(char message[5]);
void display_SetChar(char c, unsigned char pos);
void display_Write(void);

#endif
