#include "I2C.h"
#include "RealTimeClock.h"
#include "LPC1769.h"
#include <stdio.h>

#define PINSEL0		(*(unsigned int *)	0x4002C000)
#define T2MCR		(*(unsigned int *)	0x40090014)


void RTC_Init(char seconde, char minute, char hour)
{
	I2C_WriteData(RTC_SlaveAddress, RTC_Secondes_Register, (decToBcd(seconde) & 0x7F));
	I2C_WriteData(RTC_SlaveAddress, RTC_Minuten_Register, decToBcd(minute)); //min is hex 0x11
	I2C_WriteData(RTC_SlaveAddress, RTC_Hours_Register, decToBcd(hour));
	RTC_SetSQWOutput(0);

	while(1){
		printf("secondes: %d minutes: %d\n", I2C_ReadData(RTC_SlaveAddress, RTC_Secondes_Register), I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register));
	}

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

char decToBcd(char val)
{
  return (((val / 10) << 4) | (val %10));
}

char bcdToDec(char val)
{
    return (((val >> 4) * 10) + (val & 0x0F));
}

char toTime(char *time, char min, char hour)
{
    char temp[2];
    itoa(min, temp, 10); //convert to string
    if(min < 10){
        strcat(time, "0");
    }
    strcat(time, temp);

    strcat(time, ":");

    itoa(hour, temp, 10);
    if(hour < 10){
        strcat(time, "0");
    }
    strcat(time, temp);
    return time;
}
