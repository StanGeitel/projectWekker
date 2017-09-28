/*
 * display.c
 *
 *  Created on: 19 Sep 2017
 *      Author: stan
 */

#include "display.h"

void displayInit(void){
	//clearDisplay();
	//pWriteBuffer = &buffer1;
	FIO2DIR |= 0xFF;
	FIO2MASK &= ~(0xFF);
	FIO2CLR |= SHMR;
	FIO2SET |= SHMR;
}

void test1(void){
	FIO2CLR |= SHDI;
	for(int i = 0; i < 25; i++){
		FIO2CLR |= SHCLK;
		FIO2SET |= SHCLK;
	}

	FIO2SET |= RCRS;

	FIO2SET |= STCLK;
	FIO2CLR |= STCLK;

	FIO2CLR |= RCRS;

	FIO2SET |= RCCLK;
	FIO2CLR |= RCCLK;

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
		upRippleCounter();
	}
	resetRippleCounter();
}

void writeDataToShift(int row){
	for(int i = 0; i < 25; i++){
		FIO2CLR |= SHCLK;
		if((*pReadBuffer)[row] & (0x1 << i)){
			FIO2SET |=SHDI;
		}
		else {
			FIO2CLR |=SHDI;
		}
		FIO2SET |= SHCLK;
	}
}

void writeDataToStorage(void){
	FIO2CLR |= STCLK;
	FIO2SET |= STCLK;
}

void turnOnRow(int row){
	for(int i = 0; i < row; i++){
		upRippleCounter();
	}
}

void upRippleCounter(void){
	FIO2SET |= RCCLK;
	FIO2CLR |= RCCLK;
}

void resetRippleCounter(void){
	FIO2SET |= RCRS;
	FIO2CLR |= RCRS;
}

void clearDisplay(void){
	FIO2CLR |= SHMR;
	FIO2SET |= SHMR;
}

void clearRows(void){
	memset((*pWriteBuffer), 0, sizeof((*pWriteBuffer)));
}

void clearCharacter(int pos){
	for(int i = 0; i < 7; i++){
		(*pWriteBuffer)[i] &= ~(0x1F << (pos * 5));
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
