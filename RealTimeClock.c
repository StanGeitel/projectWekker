
#include "RealTimeClock.h"

void RTC_Init()
{
	I2C_WriteData(RTC_SlaveAddress, RTC_Secondes_Register, 0x00);
	I2C_WriteData(RTC_SlaveAddress, RTC_Hours_Register, 0x00);
	RTC_SetSQWOutput(0);

}

unsigned char RTC_GetMinutes()
{
	return RTC_ReadData(RTC_SlaveAddress, RTC_Minuten_Register);
}

unsigned char RTC_GetHours()
{
	return RTC_ReadData(RTC_SlaveAddress, RTC_Hours_Register);
}

void RTC_SetSQWOutput(int Hz)
{
	switch(Hz){
		case 0: //1Hz
			RTC_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x10);
			break;
		case 1: //4.096kHz
			RTC_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x11);
			break;
		case 2: //8.192kHz
			RTC_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x12);
			break;
		case 3: //32.768kHz
			RTC_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x13);
			break;
		case 4: //logic 0
			RTC_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x00);
			break;
		case 5: //logic 1
			RTC_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x80);
			break;
	}
}

void RTC_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data)
{
	I2C_WriteData(slaveAddress, dataRegister, data);
}

unsigned char RTC_ReadData(unsigned char slaveAddress, unsigned char dataRegister)
{
	return I2C_ReadData(slaveAddress, dataRegister);
}

void setTime(void){
	char (*pTime)[5] = &rtcTime;
	(*pTime)[0] = (char)RTC_GetHours() / 10;
	(*pTime)[1] = (char)RTC_GetHours() % 10;
	(*pTime)[2] = ':';
	(*pTime)[3] = (char)RTC_GetMinutes() / 10;
	(*pTime)[4] = (char)RTC_GetMinutes() % 10;
}

char* getTime(void){
	char (*pTime)[5] = &rtcTime;
	return (*pTime);
}
