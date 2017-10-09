#include "LPC1769.h"
#include "I2C.h"


void I2C_Init()
{
	PCONP |= 1 << 7;
	PCLKSEL0 |= 1 << 15;

	PIN_SEL1 |= 1 << 22;
	PIN_SEL1 |= 1 << 24;

	I2C_SCLH = (I2C_SCLH & ~0xFFFF) | 30;
	I2C_SCLL = (I2C_SCLL & ~0xFFFF) | 30;
	I2C_CONSET = I2C_Conset_I2EN; //set i2c enable
}

void I2C_SendStartBit()
{
	I2C_CONSET = I2C_Conset_STA;
}

void I2C_SendStopBit()
{
	I2C_CONSET = I2C_Conset_STO;
}

void I2C_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data)
{
	/*Send startbit*/
	I2C_CONCLR = I2C_Conclr_SIC;
	I2C_SendStartBit();
	while((I2C_CONSET & I2C_Conset_SI) != I2C_Conset_SI);

	/*Send slaveaddress + write*/
	I2C_DAT = slaveAddress & 0xFE;
	I2C_CONCLR = I2C_Conclr_SIC | I2C_Conclr_STAC;
	while((I2C_CONSET & I2C_Conset_SI) != I2C_Conset_SI);

	/*Select register*/
	I2C_DAT = dataRegister;
	I2C_CONCLR = I2C_Conclr_SIC;
	while((I2C_CONSET & I2C_Conset_SI) != I2C_Conset_SI);

	/*Write data*/
	I2C_DAT = data;
	I2C_CONCLR = I2C_Conclr_SIC;
	while((I2C_CONSET & I2C_Conset_SI) != I2C_Conset_SI);

	/*Send stopbit*/
	I2C_SendStopBit();
	I2C_CONCLR = I2C_Conclr_SIC;
}

unsigned char I2C_ReadData(unsigned char slaveAddress, unsigned char dataRegister)
{
	char data;

	/*Select register*/
	I2C_SelectRegister(slaveAddress, dataRegister);

	/*Send startbit*/
	I2C_CONCLR = I2C_Conclr_SIC;
	I2C_SendStartBit();
	while((I2C_CONSET & I2C_Conset_SI) != I2C_Conset_SI);

	/*Send slaveaddress + read*/
	I2C_DAT = slaveAddress | 0x01;
	I2C_CONCLR = I2C_Conclr_SIC | I2C_Conclr_STAC;
	while((I2C_CONSET & I2C_Conset_SI) != I2C_Conset_SI);
	I2C_CONSET = I2C_Conset_AA;
	I2C_CONCLR = I2C_Conclr_SIC;

	/*Get data*/
	I2C_CONCLR = I2C_Conclr_AAC | I2C_Conclr_SIC;
	I2C_CONCLR = I2C_Conclr_SIC; //reset si bit
	while((I2C_CONSET & I2C_Conset_SI) != I2C_Conset_SI);
	data = I2C_DAT;

	/*Send stopbit*/
	I2C_SendStopBit();
	I2C_CONCLR = I2C_Conclr_SIC;

	return data;
}

void I2C_SelectRegister(unsigned char slaveAddress, unsigned char dataRegister)
{
	/*Send startbit*/
	I2C_CONCLR = I2C_Conclr_SIC;
	I2C_SendStartBit();
	while((I2C_CONSET & I2C_Conset_SI) != I2C_Conset_SI); //wait for si bit to set

	/*Send slaveaddress + write*/
	I2C_DAT = slaveAddress & 0xFE;
	I2C_CONCLR = I2C_Conclr_SIC | I2C_Conclr_STAC; //reset si bit and start
	while((I2C_CONSET & I2C_Conset_SI) != I2C_Conset_SI); //wait for si bit to set

	/*Select register*/
	I2C_DAT = dataRegister;
	I2C_CONCLR = I2C_Conclr_SIC; //reset si bit
	while((I2C_CONSET & I2C_Conset_SI) != I2C_Conset_SI); //wait for si bit to set

	/*Send stopbit*/
	I2C_SendStopBit();
	I2C_CONCLR = I2C_Conclr_SIC; //reset si bit
}
