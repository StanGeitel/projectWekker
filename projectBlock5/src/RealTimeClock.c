#include "I2C.h"
#include "RealTimeClock.h"
#include "LPC1769.h"
#include "timer.h"
#include <string.h>

char time[6];

void RTC_Init(char seconde, char minute, char hour)
{
	char sec = RTC_decToBcd(seconde);
	char min = RTC_decToBcd(minute);
	char uur = RTC_decToBcd(hour);
	I2C_WriteData(RTC_SlaveAddress, RTC_Secondes_Register, sec);
	I2C_WriteData(RTC_SlaveAddress, RTC_Minuten_Register, min); //min is hex 0x11
	I2C_WriteData(RTC_SlaveAddress, RTC_Hours_Register, uur);
	RTC_SetSQWOutput(0);

	timer_Init(RTC_TIMER,0);
	timer_SetCTCR(RTC_TIMER,RISING_EDGE,CAP0);
	timer_SetMCR(RTC_TIMER,MR0,0x3);
	timer_SetMR(RTC_TIMER,MR0,60);
	timer_ClearIR(RTC_TIMER);
	timer_Enable(RTC_TIMER);
}

void RTC_TIMER2_IRQHandler(void)
{
	timer_ClearIR(RTC_TIMER);
	RTC_setTime(RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register)), RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Hours_Register)));
	//printf("%s \n", RTC_getTime());
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
			//printf("RTC_SetSQWOutput(int Hz) fault! \n");
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

char* RTC_getTime(){
	return time;
}

void RTC_setTime(int min, int hour){
    if(min > 9){
        time[0] = (min/10%10) + '0';
        time[1] = (min%10) + '0';
    }else{
        time[0] = '0';
        time[1] = (min%10) + '0';
    }
    time[2] = ':';
    if(hour > 9){
        time[3] = (hour/10%10) + '0';
        time[4] = (hour%10) + '0';
    }else{
        time[3] = '0';
        time[4] = (hour%10) + '0';
    }
}
