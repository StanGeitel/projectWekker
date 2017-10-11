#include "timer.h"
#include "I2C.h"
#include "LPC1769.h"
#include "alarm.h"
#include "RealTimeClock.h"

#define RTC_TIMER 				TIMER3

void RTC_Init(void)
{
	I2C_Init();
	RTC_SetSQWOutput(0);

	timer_Init(RTC_TIMER,0);
	timer_ClearIR(RTC_TIMER);
	timer_SetCTCR(RTC_TIMER,FALING_EDGE,CAP1);
	timer_SetMR(RTC_TIMER,MR0,20);
	timer_SetMCR(RTC_TIMER,MR0,0x3);


	timer_Enable(RTC_TIMER);

	alarm_print(RTC_ReadData(RTC_Minuten_Register),RTC_ReadData(RTC_Hours_Register));
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
//			printf("RTC_SetSQWOutput(int Hz) fault! \n");
			break;
	}
}

void RTC_WriteData(unsigned char dataRegister, char data)
{
	I2C_WriteData(RTC_SlaveAddress, dataRegister, data);
}

unsigned char RTC_ReadData(unsigned char dataRegister)
{
	return I2C_ReadData(RTC_SlaveAddress, dataRegister);
}

char RTC_decToBcd(char val)
{
	return (((val / 10) << 4) | (val %10));
}

char RTC_bcdToDec(char val)
{
    return (((val >> 4) * 10) + (val & 0x0F));
}
