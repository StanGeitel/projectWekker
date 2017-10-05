#include <stdbool.h>
#include <stdlib.h>
#include "LPC1769.h"
#include "GPIO.h"
#include "RIT.h"
#include "display.h"
#include "font5x7.h"
#include "SPI.h"

volatile bool displayUpdate = false;
unsigned char row = 0;

int arr[7];

int *frontBuffer;
int *backBuffer;

void display_Init(void){
	SPI_Init();
	GPIO_SetDIR(DISPLAY_IOPORT,0x30003);
	GPIO_Clear(DISPLAY_IOPORT, H_STO);								//set H_STO LOW(this has no effect until STO is set to GPIO

	H_RST(LOW);														//reset the shift registers
	V_RST(HIGH);													//reset the row counter
	H_RST(HIGH);
	V_RST(LOW);

	frontBuffer = malloc(7 * sizeof(int));							//allocate memory for the frontBuffer
	backBuffer = malloc(7 * sizeof(int));							//allocate memory for the backbuffer

	memset(frontBuffer,0,7*sizeof(int));							//set whole frontBuffer low
	memset(backBuffer,0,7*sizeof(int));								//set whole backBuffer low

	RIT_Init();
	RIT_SetCOMP(6666);
	RIT_Enable();

	timer_Init(DISPLAY_TIMER,500);
	timer_Reset(DISPLAY_TIMER);
	timer_SetMR(DISPLAY_TIMER,MR0,10);
	timer_SetMCR(DISPLAY_TIMER,MR0,0x3);
	timer_Enable(DISPLAY_TIMER);
}

void display_Set(char *message){										//write char array to backBuffer
	for(unsigned char pos = 0; pos < 5; pos++){
		display_SetChar(message[4 - pos],pos);
	}
}

void display_SetChar(char c, unsigned char pos){						//write char to backBuffer
	while(displayUpdate);
	c -= 32;															//first 32 characters in the ASCII table are commands
	for(unsigned char horizontal = 0; horizontal < 5; horizontal++){	//write the character data into the buffer
		for(unsigned char vertical = 0; vertical < 7; vertical++){
			backBuffer[6 - vertical] |= ((Font5x7[c][4 - horizontal] >> vertical) & 1) << (horizontal + 5 * pos);
		}
	}
}

void display_Write(void){
	displayUpdate = true;												//updates the frontBuffer when it is not being red
}

void RIT_IRQHandler(void){
	if(row < 7){
		SPI_WriteInteger(~0);											//clear current row
		timer_SetPR(DISPLAY_TIMER,500);									//set prescaler back to its original value

		while(!(GPIO_Read(DISPLAY_IOPORT) & H_STO));								//wait until H_STO is high so you know the row is cleared

		V_CLK(HIGH);													//up the row counter
		V_CLK(LOW);

		SPI_WriteInteger(~frontBuffer[row]);							//write data to the new row

		row++;
	}else if(row == 7){													//if all row's have been written
		V_RST(HIGH);													//reset the row counter
		V_RST(LOW);

		if(displayUpdate){												//if new data is ready
			int *temp = frontBuffer;										//Temporally store the base address of the current frontBuffer
			frontBuffer = backBuffer;									//set the base address of the backBuffer with all its new data in frontBuffer
			backBuffer = temp;											//set the previous base address of the frontBuffer in backBuffer;
			memset(backBuffer,0,7*sizeof(int));							//clear the backBuffer of data
			displayUpdate = false;
		}
	}else if(row == 9){
		row = 0;
	}
	RIT_ClearIR();
}
