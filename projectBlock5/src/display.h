
#ifndef DISPLAY_H_
#define DISPLAY_H_

#define DISPLAY_IOPORT	PORT0
#define HIGH 	1
#define LOW		0
#define H_STO	1 << 16
#define H_RST(x)	{x ? GPIO_Set(PORT0,1 << 17) : GPIO_Clear(PORT0,1 << 17);}
#define V_CLK(x)	{x ? GPIO_Set(PORT0,1 << 1) : GPIO_Clear(PORT0,1 << 1);}
#define V_RST(x)	{x ? GPIO_Set(PORT0,1 << 0) : GPIO_Clear(PORT0,1 << 0);}
#define REFRESH_RATE 60
#define DELAY	800

void display_Init(void);
void display_SetCursor(unsigned char pos);
void display_EnableCursor(void);
void display_DisableCursor(void);
void display_Set(char message[5]);
void display_SetChar(char c, unsigned char pos);
void display_Write(void);

#endif
