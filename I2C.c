#include <stdio.h>
#include "I2C.h"


void I2C_Init()
{
	PCONP |= 0x8000;
	PCLKSEL1 |= 0x40;
	I2C1SCLH |= 75;
	I2C1SCLL |= 75;
	PINSEL0 |= 0x30F; //select pin sda1 (P0.0) and scl1 (P0.1) and CAP2.0 (P0.4)
	I2C1CONSET = I2C_Conset_I2EN; //set i2c enable
}

void I2C_SendStartBit()
{
	I2C1CONSET = I2C_Conset_STA;
}

void I2C_SendStopBit()
{
	I2C1CONSET = I2C_Conset_STO;
}

void I2C_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data)
{
	/*Send startbit*/
	I2C1CONCLR = I2C_Conclr_SIC;
	I2C_SendStartBit();
	while((I2C1CONSET & I2C_Conset_SI) != I2C_Conset_SI);

	/*Send slaveaddress + write*/
	I2C1DAT = slaveAddress & 0xFE;
	I2C1CONCLR = I2C_Conclr_SIC | I2C_Conclr_STAC;
	while((I2C1CONSET & I2C_Conset_SI) != I2C_Conset_SI);

	/*Select register*/
	I2C1DAT = dataRegister;
	I2C1CONCLR = I2C_Conclr_SIC;
	while((I2C1CONSET & I2C_Conset_SI) != I2C_Conset_SI);

	/*Write data*/
	I2C1DAT = data;
	I2C1CONCLR = I2C_Conclr_SIC;
	while((I2C1CONSET & I2C_Conset_SI) != I2C_Conset_SI);

	/*Send stopbit*/
	I2C_SendStopBit();
	I2C1CONCLR = I2C_Conclr_SIC;
}

unsigned char I2C_ReadData(unsigned char slaveAddress, unsigned char dataRegister)
{
	char data;

	/*Select register*/
	I2C_SelectRegister(slaveAddress, dataRegister);

	/*Send startbit*/
	I2C1CONCLR = I2C_Conclr_SIC;
	I2C_SendStartBit();
	while((I2C1CONSET & I2C_Conset_SI) != I2C_Conset_SI);

	/*Send slaveaddress + read*/
	I2C1DAT = slaveAddress | 0x01;
	I2C1CONCLR = I2C_Conclr_SIC | I2C_Conclr_STAC;
	while((I2C1CONSET & I2C_Conset_SI) != I2C_Conset_SI);
	I2C1CONSET = I2C_Conset_AA;
	I2C1CONCLR = I2C_Conclr_SIC;

	/*Get data*/
	I2C1CONCLR = I2C_Conclr_AAC | I2C_Conclr_SIC;
	I2C1CONCLR = I2C_Conclr_SIC; //reset si bit
	while((I2C1CONSET & I2C_Conset_SI) != I2C_Conset_SI);
	data = I2C1DAT;

	/*Send stopbit*/
	I2C_SendStopBit();
	I2C1CONCLR = I2C_Conclr_SIC;

	return data;
}

void I2C_SelectRegister(unsigned char slaveAddress, unsigned char dataRegister)
{
	/*Send startbit*/
	I2C1CONCLR = I2C_Conclr_SIC;
	I2C_SendStartBit();
	while((I2C1CONSET & I2C_Conset_SI) != I2C_Conset_SI); //wait for si bit to set

	/*Send slaveaddress + write*/
	I2C1DAT = slaveAddress & 0xFE;
	I2C1CONCLR = I2C_Conclr_SIC | I2C_Conclr_STAC; //reset si bit and start
	while((I2C1CONSET & I2C_Conset_SI) != I2C_Conset_SI); //wait for si bit to set

	/*Select register*/
	I2C1DAT = dataRegister;
	I2C1CONCLR = I2C_Conclr_SIC; //reset si bit
	while((I2C1CONSET & I2C_Conset_SI) != I2C_Conset_SI); //wait for si bit to set

	/*Send stopbit*/
	I2C_SendStopBit();
	I2C1CONCLR = I2C_Conclr_SIC; //reset si bit
}
