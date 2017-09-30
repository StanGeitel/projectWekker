/*
 * display.c
 *
 *  Created on: 19 Sep 2017
 *      Author: stan
 */

#include "display.h"

void displayInit(void){
	FIO2DIR = 0x1DC0;
	resetShiftRegister();
	resetRippleCounter();
	pWriteBuffer = &buffer1;
}

void setMessage(char message[5]){
	clearRows();
	int pos = 0;
	for(int i = 4; i >= 0; i--){
		if(pos <= 5){
		 setCharacter(message[i], pos);
		 pos++;
		}
	}
	swapBuffer();
}

void writeToDisplay(void){
	for(int i = 0; i < 7; i++){
	//Beginning of SPI
		writeHigh();
		upRippleCounter();
		writeDataToShift(i);
		shiftToStorage();
	//End of SPI
	}
	resetRippleCounter();
}

//Van hier
void writeDataToShift(int row){
	for(int i = 0; i < 25; i++){
		if((*pReadBuffer)[row] & (0x1 << i)){
			FIO2SET = SHDI;
		}
		else {
			FIO2CLR = SHDI;
		}
		shiftData();
	}
}

void writeHigh(void){
	FIO2SET = SHDI;
	for(int i = 0; i < 25; i++){
		shiftData();
	}
	shiftToStorage();
}

void shiftData(void){
	FIO2CLR = SHCLK;
	FIO2SET = SHCLK;
}

void shiftToStorage(void){
	FIO2CLR = STCLK;
	FIO2SET = STCLK;
}
//tot hier is straks overbodig

void upRippleCounter(void){
	FIO2SET = RCCLK;
	FIO2CLR = RCCLK;
}

void resetRippleCounter(void){
	FIO2SET = RCRS;
	FIO2CLR = RCRS;
}

void resetShiftRegister(void){
	FIO2CLR = SHMR;
	FIO2SET = SHMR;
}

void clearRows(void){
	memset((*pWriteBuffer), 0xFF, sizeof((*pWriteBuffer)));
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
	case 42:		{data[0]=0x00; data[1]=0x00; data[2]=0x0A; data[3]=0x04; data[4]=0x0A; data[5]=0x00; data[6]=0x00;}	// *
	break;
	case 43:		{data[0]=0x00; data[1]=0x00; data[2]=0x04; data[3]=0x0E; data[4]=0x04; data[5]=0x00; data[6]=0x00;}	// +
	break;
	case 45:		{data[0]=0x00; data[1]=0x00; data[2]=0x00; data[3]=0x0E; data[4]=0x00; data[5]=0x00; data[6]=0x00;}	// -
	break;
	case 47:		{data[0]=0x00; data[1]=0x04; data[2]=0x00; data[3]=0x0E; data[4]=0x00; data[5]=0x04; data[6]=0x00;}	// /
	break;
	case 48:		{data[0]=0x00; data[1]=0x0E; data[2]=0x0A; data[3]=0x0A; data[4]=0x0A; data[5]=0x0E; data[6]=0x00;}	// 0
	break;
	case 49:		{data[0]=0x00; data[1]=0x04; data[2]=0x0C; data[3]=0x04; data[4]=0x04; data[5]=0x0E; data[6]=0x00;}	// 1
	break;
	case 50:		{data[0]=0x00; data[1]=0x0E; data[2]=0x02; data[3]=0x0E; data[4]=0x08; data[5]=0x0E; data[6]=0x00;}	// 2
	break;
	case 51:		{data[0]=0x00; data[1]=0x0E; data[2]=0x02; data[3]=0x0E; data[4]=0x02; data[5]=0x0E; data[6]=0x00;}	// 3
	break;
	case 52:		{data[0]=0x00; data[1]=0x0A; data[2]=0x0A; data[3]=0x0E; data[4]=0x02; data[5]=0x02; data[6]=0x00;}	// 4
	break;
	case 53:		{data[0]=0x00; data[1]=0x0E; data[2]=0x08; data[3]=0x0E; data[4]=0x02; data[5]=0x0E; data[6]=0x00;}	// 5
	break;
	case 54:		{data[0]=0x00; data[1]=0x0E; data[2]=0x08; data[3]=0x0E; data[4]=0x0A; data[5]=0x0E; data[6]=0x00;}	// 6
	break;
	case 55:		{data[0]=0x00; data[1]=0x0E; data[2]=0x02; data[3]=0x02; data[4]=0x02; data[5]=0x02; data[6]=0x00;}	// 7
	break;
	case 56:		{data[0]=0x00; data[1]=0x0E; data[2]=0x0A; data[3]=0x0E; data[4]=0x0A; data[5]=0x0E; data[6]=0x00;}	// 8
	break;
	case 57:		{data[0]=0x00; data[1]=0x0E; data[2]=0x0A; data[3]=0x0E; data[4]=0x02; data[5]=0x0E; data[6]=0x00;}	// 9
	break;
	case 58:		{data[0]=0x00; data[1]=0x00; data[2]=0x02; data[3]=0x00; data[4]=0x02; data[5]=0x00; data[6]=0x00;}	// :
	break;
	default:
	break;
	}
	for(int i = 0; i < 7; i++){
		(*pWriteBuffer)[i] &= ~(data[i] << (pos * 5));
	}
}
