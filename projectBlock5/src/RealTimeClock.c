#include "I2C.h"
#include "RealTimeClock.h"
#include "LPC1769.h"
#include "timer.h"
#include "alarm.h"
#include "display.h"

void RTC_Init(char seconde, char minute, char hour)
{
	I2C_Init();
	char sec = RTC_decToBcd(seconde);
	char min = RTC_decToBcd(minute);
	char uur = RTC_decToBcd(hour);

	I2C_WriteData(RTC_SlaveAddress, RTC_Secondes_Register, sec);
	I2C_WriteData(RTC_SlaveAddress, RTC_Minuten_Register, min); //min is hex 0x11
	I2C_WriteData(RTC_SlaveAddress, RTC_Hours_Register, uur);

	RTC_WriteData(RTC_SlaveAddress, Alarm_Minuts_Register, 0x00);
	RTC_WriteData(RTC_SlaveAddress, Alarm_Hours_Register, 0x00);

	RTC_SetSQWOutput(0);

	timer_Init(TIMER3,0);
	timer_Disable(TIMER3);
	timer_ClearIR(TIMER3);
	timer_SetCTCR(TIMER3,FALING_EDGE,CAP1);
	timer_SetMR(TIMER3,MR0,10);
	timer_SetMCR(TIMER3,MR0,0x3);

	timer_Enable(TIMER3);

	alarm_setTime(RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register)), RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Hours_Register)));
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

void RTC_WriteData(unsigned char slaveAddress, unsigned char dataRegister, char data)
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

void TIMER3_IRQHandler(void){
	//timer_ClearIR(RTC_TIMER);
	timer_ClearIR(TIMER3);
	//RTC_setTime(RTC_getMinuts(), RTC_getHours());
	alarm_setTime(RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register)), RTC_bcdToDec(I2C_ReadData(RTC_SlaveAddress, RTC_Hours_Register)));
}




void RTC_setTime(unsigned char min, unsigned char hour){
	RTC_printTime(min, hour);

	if((RTC_getMinuts() == RTC_getAlarmMinuts()) && (RTC_getHours() == RTC_getAlarmHours())){
		alarm_TurnOn();
	}
}

void RTC_SetAlarmTime(char number, int posAlarmTime){
	switch(posAlarmTime){
	case 0:		RTC_WriteData(RTC_SlaveAddress, Alarm_Minuts_Register, ((RTC_getAlarmMinuts() & ~0xF) | number));
		break;
	case 1:		RTC_WriteData(RTC_SlaveAddress, Alarm_Minuts_Register, ((RTC_getAlarmMinuts() & ~(0xF << 4)) | (number << 4)));
		break;
	case 2:		RTC_WriteData(RTC_SlaveAddress, Alarm_Hours_Register, ((RTC_getAlarmHours() & ~0xF) | number));
		break;
	case 3:		RTC_WriteData(RTC_SlaveAddress, Alarm_Hours_Register, ((RTC_getAlarmHours()  & ~(0xF << 4)) | (number << 4)));
		break;
	}
	RTC_printTime(RTC_getAlarmMinuts(), RTC_getAlarmHours());
}

void RTC_printTime(unsigned char min, unsigned char hour){
	char RTC_time[5];
    RTC_time[0] = (min & 0xF) + '0' ;
    RTC_time[1] = ((min >> 4) & 0xF) + '0';
    RTC_time[2] = ':';
    RTC_time[3] = (hour & 0xF) + '0';
    RTC_time[4] = ((hour >> 4) & 0xF) + '0';

    display_Set(RTC_time);
    display_Write();
}

unsigned char RTC_getMinuts(void){
	return I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register);
}

unsigned char RTC_getHours(void){
	return I2C_ReadData(RTC_SlaveAddress, RTC_Minuten_Register);
}

unsigned char RTC_getAlarmMinuts(void){
	return RTC_ReadData(RTC_SlaveAddress, Alarm_Minuts_Register);
}

unsigned char RTC_getAlarmHours(void){
	return RTC_ReadData(RTC_SlaveAddress, Alarm_Hours_Register);
}


