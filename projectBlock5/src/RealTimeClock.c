#include "I2C.h"
#include "RealTimeClock.h"
#include "LPC1769.h"
#include "timer.h"
#include "display.h"
#include <stdio.h>

char RTC_time[5] =  {'0','0',':','0','0'};

void RTC_Init(char seconde, char minute, char hour)
{
	//I2C_Init();
	char sec = RTC_decToBcd(seconde);
	char min = RTC_decToBcd(minute);
	char uur = RTC_decToBcd(hour);

	I2C_WriteData(RTC_SlaveAddress, RTC_Secondes_Register, sec);
	I2C_WriteData(RTC_SlaveAddress, RTC_Minuten_Register, min); //min is hex 0x11
	I2C_WriteData(RTC_SlaveAddress, RTC_Hours_Register, uur);
	RTC_SetSQWOutput(0);

	timer_Init(TIMER3,0);
	timer_Disable(TIMER3);
	timer_ClearIR(TIMER3);
	timer_SetCTCR(TIMER3,FALING_EDGE,CAP1);
	timer_SetMR(TIMER3,MR0,10);
	timer_SetMCR(TIMER3,MR0,0x3);

	timer_Enable(TIMER3);

	printf("a \n");
}

void TIMER3_IRQHandler(void)
{
	//timer_ClearIR(RTC_TIMER);
	timer_ClearIR(TIMER3);
	printf("it works \n");
	printf("min: %d, uur: %d \n", RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register)), RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Hours_Register)));
	RTC_setTime(RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register)), RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Hours_Register)));
}

void RTC_SetSQWOutput(int Hz)
{
	switch(Hz){
		case 0: //1Hz
			I2C_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x10);
			break;
		case 1: //4.096kHz
			I2C_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x11);
			break;
		case 2: //8.192kHz
			I2C_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x12);
			break;
		case 3: //32.768kHz
			I2C_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x13);
			break;
		case 4: //logic 0
			I2C_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x00);
			break;
		case 5: //logic 1
			I2C_WriteData(RTC_SlaveAddress, RTC_Control_Register, 0x80);
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
	return I2C_ReadData(slaveAddress, dataRegister);
}

char RTC_decToBcd(char val)
{
	return (((val / 10) << 4) | (val %10));
}

char RTC_bcdToDec(char val)
{
    return (((val >> 4) * 10) + (val & 0x0F));
}

void RTC_setTime(int min, int hour){
    RTC_time[0] = (char)(min/10) + '0';
    RTC_time[1] = (char)(min%10) + '0';
    RTC_time[2] = ':';
    RTC_time[3] = (char)(hour/10) + '0';
    RTC_time[4] = (char)(hour%10) + '0';
    display_Set("Hello");
    display_Write();
}

char* RTC_getTime(){
	return RTC_time;
}
