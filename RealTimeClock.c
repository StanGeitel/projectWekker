#define RTC_Secondes_Register  	0x00
#define RTC_Minuten_Register   	0x01
#define RTC_Hours_Register 	  	0x02
#define RTC_Day_Register 		0x03
#define RTC_Date_Register 	  	0x04
#define RTC_Month_Register   	0x05
#define RTC_Year_Register   	0x06
#define RTC_Control_Register   	0x07
#define RTC_SlaveAddress		0xD0

#include "I2C.h"
#include "RealTimeClock.h"
#include <stdio.h>

char minutes = 0;
char hours = 0;

void RTC_Init()
{
	I2C_WriteData(RTC_SlaveAddress, RTC_Secondes_Register, 0x00);
	delay1(); //change to timer in stead of for loop
	I2C_WriteData(RTC_SlaveAddress, RTC_Hours_Register, 0x00);
	delay1();
	RTC_SetSQWOutput(0);
	delay1();

	/*read is still in progress*/
	char a;
	while(1){
		a = I2C_ReadData(0xD0, 0x00);
		printf("data: %d \n", a);
	}
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
		default:
			printf("RTC_SetSQWOutput(int Hz) fault! \n");
			break;
	}
}

void RTC_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data)
{
	I2C_WriteData(slaveAddress, dataRegister, data);
}

unsigned char RTC_ReadData(unsigned char slaveAddress, unsigned char dataRegister)
{
	I2C_ReadData(slaveAddress, dataRegister);
}
