/*
 * display.c
 *
 *  Created on: 19 Sep 2017
 *      Author: stan
 */

#include "display.h"

void displayInit(void){
	clearDisplay();
	pWriteBuffer = &buffer1;
	writeGpio(RCRS, 0);
}

void setMessage(char message[5]){
	clearRows();
	int pos = 0;
	for(int i = 4; i >= 0; i--){
		setCharacter(message[i], pos);
		pos++;
	}

	swapBuffer();
}

void writeToDisplay(void){
	clearDisplay();
	for(int i = 0; i < 7; i++){
		writeDataToShift(i);
		writeDataToStorage();
		turnOnRow(i);
		resetRippleCounter();
	}
}

void writeDataToShift(int row){
	for(int i = 0; i < 25; i++){
		writeGpio(SHCLK, 0);
		writeGpio(SHDI, ((*pReadBuffer)[row] & (0x1 << i)));
		writeGpio(SHCLK, 1);
	}
}

void writeDataToStorage(void){
	writeGpio(STCLK, 0);
	writeGpio(STCLK, 1);
}

void turnOnRow(int row){
	for(int i = 0; i < row; i++){
		upRippleCounter();
	}
}

void upRippleCounter(void){
	writeGpio(RCCLK, 0);
	writeGpio(RCCLK, 1);
}

void resetRippleCounter(void){
	writeGpio(RCRS, 1);
	writeGpio(RCRS, 0);
}

void clearDisplay(void){
	writeGpio(SHMR, 0);
	writeGpio(SHMR, 1);
}

void clearRows(void){
	memset((*pWriteBuffer), 0, sizeof((*pWriteBuffer)));
}

void clearCharacter(int pos){
	for(int i = 0; i < 7; i++){
		(*pWriteBuffer)[i] &= ~(0x1F << (pos * 5));
	}
}

void writeGpio(int pin, int state){
	if(state){
		GPIO_Set(GPIO, pin);
	}
	else{
		GPIO_Clear(GPIO, pin);
	}
}

void swapBuffer(void){
	if(pReadBuffer == &buffer1){
		pReadBuffer = &buffer2;
		pWriteBuffer = &buffer1;
	}
	else{
		pReadBuffer = &buffer1;
		pWriteBuffer = &buffer2;
	}
}

void setCharacter(char c, int pos){
	char data[7];
	switch(c){
	case 42:		{data[0]=0x00; data[1]=0x11; data[2]=0x0A; data[3]=0x04; data[4]=0x0A; data[5]=0x11; data[6]=0x00;}	// *
	break;
	case 43:		{data[0]=0x00; data[1]=0x04; data[2]=0x04; data[3]=0x1F; data[4]=0x04; data[5]=0x04; data[6]=0x00;}	// +
	break;
	case 45:		{data[0]=0x00; data[1]=0x00; data[2]=0x00; data[3]=0x1F; data[4]=0x00; data[5]=0x00; data[6]=0x00;}	// -
	break;
	case 47:		{data[0]=0x00; data[1]=0x04; data[2]=0x00; data[3]=0x1F; data[4]=0x00; data[5]=0x04; data[6]=0x00;}	// /
	break;
	case 48:		{data[0]=0x1F; data[1]=0x11; data[2]=0x11; data[3]=0x11; data[4]=0x11; data[5]=0x11; data[6]=0x1F;}	// 0
	break;
	case 49:		{data[0]=0x04; data[1]=0x0C; data[2]=0x04; data[3]=0x04; data[4]=0x04; data[5]=0x04; data[6]=0x0E;}	// 1
	break;
	case 50:		{data[0]=0x1F; data[1]=0x01; data[2]=0x01; data[3]=0x1F; data[4]=0x10; data[5]=0x10; data[6]=0x1F;}	// 2
	break;
	case 51:		{data[0]=0x1F; data[1]=0x01; data[2]=0x01; data[3]=0x1F; data[4]=0x01; data[5]=0x01; data[6]=0x1F;}	// 3
	break;
	case 52:		{data[0]=0x11; data[1]=0x11; data[2]=0x11; data[3]=0x1F; data[4]=0x01; data[5]=0x01; data[6]=0x01;}	// 4
	break;
	case 53:		{data[0]=0x1F; data[1]=0x10; data[2]=0x10; data[3]=0x1F; data[4]=0x01; data[5]=0x01; data[6]=0x1F;}	// 5
	break;
	case 54:		{data[0]=0x1F; data[1]=0x10; data[2]=0x10; data[3]=0x1F; data[4]=0x11; data[5]=0x11; data[6]=0x1F;}	// 6
	break;
	case 55:		{data[0]=0x1F; data[1]=0x01; data[2]=0x01; data[3]=0x01; data[4]=0x01; data[5]=0x01; data[6]=0x1F;}	// 7
	break;
	case 56:		{data[0]=0x1F; data[1]=0x11; data[2]=0x11; data[3]=0x1F; data[4]=0x11; data[5]=0x11; data[6]=0x1F;}	// 8
	break;
	case 57:		{data[0]=0x1F; data[1]=0x11; data[2]=0x11; data[3]=0x1F; data[4]=0x01; data[5]=0x01; data[6]=0x1F;}	// 9
	break;
	case 58:		{data[0]=0x00; data[1]=0x04; data[2]=0x00; data[3]=0x00; data[4]=0x00; data[5]=0x04; data[6]=0x00;}	// :
	break;
	}
	for(int i = 0; i < 7; i++){
		(*pWriteBuffer)[i] |= (data[i] << (pos * 5));
	}
}
