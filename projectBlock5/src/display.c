
#include <stdbool.h>
#include <stdlib.h>
#include "LPC1769.h"
#include "GPIO.h"
#include "timer.h"
#include "display.h"
#include "font5x7.h"
#include "SPI.h"

bool displayUpdate = false;
unsigned char row = 0;

int *backBuffer;
int *frontBuffer;

void display_Init(void){
	SPI_Init();
	GPIO_SetDIR(PORT,0x30003);
	GPIO_Clear(PORT,1 << 16);

	H_RST(LOW);
	V_RST(HIGH);
	H_RST(HIGH);
	V_RST(LOW);

	frontBuffer = malloc(7 * sizeof(int));
	backBuffer = malloc(7 * sizeof(int));

	timer_Init(TIMER, 666);
	timer_SetMR(TIMER,MR0,10);
	timer_SetMCR(TIMER,MR0,0x3);
	timer_Enable(TIMER);
}

void display_Set(char message[5]){
	for(unsigned char pos = 4; pos >= 0; pos--){
		display_SetChar(message[4 - pos], pos);
	}
}

void display_SetChar(char c, unsigned char pos){
	for(unsigned char row = 0; row < 7; row++){
		backBuffer[row] = (Font5x7[c - 32][row] << (pos * 5));
	}
}

void display_Write(void){
	displayUpdate = true;
}

void TIMER1_IRQHandler(void){
	if(row < 7){
		SPI_WriteInteger(0);
		timer_SetPR(TIMER,666);
		while(!(GPIO_Read(PORT) & (1 << 16)));

		V_CLK(HIGH);
		V_CLK(LOW);

		SPI_WriteInteger(~frontBuffer[row]);

		row++;
	}else if(row == 7){
		timer_SetPR(TIMER,1332);

		V_RST(HIGH);
		V_RST(LOW);

		if(displayUpdate){
			frontBuffer = realloc(backBuffer,7* sizeof(int));
			calloc(*backBuffer,7*sizeof(int));
			displayUpdate = false;
		}
		row = 0;
	}

	timer_ClearIR(TIMER);
}
