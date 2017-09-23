#define I2C0CONSET  (*(unsigned int *)	0x4001C000) // Control Set Register
#define I2C0DAT  	(*(unsigned int *)	0x4001C008) // dataregister
#define I2C0CONCLR  (*(unsigned int *)	0x4001C018) // clear control register
#define I2C0SCLH  	(*(unsigned int *)	0x4001C010) // SCH Duty Cycle Register High Half Word
#define I2C0SCLL  	(*(unsigned int *)	0x4001C014) // SCL Duty Cycle Register Low Half Word
#define PINSEL1  	(*(unsigned int *)	0x4002C004) // Pinselect register
#define I2C0STAT  	(*(unsigned int *)	0x4001C004) // I2C status register

#define PCONP  		(*(unsigned int *)	0x400FC0C4)
#define PCLKSEL0  	(*(unsigned int *)	0x400FC1A8)

#include <stdio.h>
#include "I2C.h"


void I2C_Init(void)
{
	PCONP |= 0x80;
	PCLKSEL0 |= 0x4000;
	I2C0CONCLR = 0x6C;
	I2C0CONSET = 0x40;
	I2C0SCLH = 50;
	I2C0SCLL = 50;
	PINSEL1 |= 0x1400000;
}

void I2C_SendStartBit()
{
	I2C0CONSET = 0x20;
}

void I2C_SendStopBit()
{
	I2C0CONSET = 0x10;
}

void I2C_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data)
{
	I2C_SendStartBit();
	while((I2C0CONSET & 0x08) != 0x08);
	I2C0CONCLR = 0x28;

	I2C0DAT = slaveAddress & 0xFE;
	while((I2C0CONSET & 0x08) != 0x08);
	I2C0CONCLR = 0x28;

	I2C0DAT = dataRegister;
	while((I2C0CONSET & 0x08) != 0x08);
	I2C0CONCLR = 0x28;

	I2C0DAT = data;
	while((I2C0CONSET & 0x08) != 0x08);
	I2C0CONCLR = 0x28;

	I2C_SendStopBit();
}

unsigned char I2C_ReadData(unsigned char slaveAddress, unsigned char dataRegister) //still in progress
{
	char data;

	//I2C0CONCLR = 0x6C; // clear all bits
	//I2C0CONSET = 0x40; //set i2c enable

	/*I2C_SendStartBit();
	while((I2C0CONSET & 0x08) != 0x08);
	I2C0CONCLR = 0x28;

	I2C0DAT = 0xD0 & 0xFE; // slave address + read(1)
	while((I2C0CONSET & 0x08) != 0x08);
	I2C0CONCLR = 0x28;

	I2C0DAT = 0x00;
	while((I2C0CONSET & 0x08) != 0x08);
	I2C0CONCLR = 0x28;

	delay1();*/

	I2C_SendStartBit();

	while((I2C0CONSET & 0x08) != 0x08);
	I2C0CONCLR = 0x28;

	I2C0DAT = 0xD0 | 0x01;
	while((I2C0CONSET & 0x08) != 0x08);
	I2C0CONCLR = 0x28;

	printf("delay \n");

	data = I2C0DAT;

	/*I2C0CONSET = 0x04; //send ack
	while((I2C0CONSET & 0x08) != 0x08);
	I2C0CONCLR = 0x28;

	data = I2C0DAT;*/

	I2C0CONCLR = 0x04; //send nack

	I2C_SendStopBit();

	return data;
}

void delay1(){ //user timer instead of for loop!!
	for(int i = 0 ; i < 10 ; i++){
		printf("a");
	}
	printf("\n");
}
