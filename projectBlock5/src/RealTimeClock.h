
#ifndef REALTIMECLOCK_H_
#define REALTIMECLOCK_H_

#define RTC_Secondes_Register  	0x00
#define RTC_Minuten_Register   	0x01
#define RTC_Hours_Register 	  	0x02
#define RTC_Day_Register 		0x03
#define RTC_Date_Register 	  	0x04
#define RTC_Month_Register   	0x05
#define RTC_Year_Register   	0x06
#define RTC_Control_Register   	0x07
#define RTC_Status_Register		0x08
#define Alarm_Minuts_Register	0x08
#define Alarm_Hours_Register	0x09
#define RTC_SlaveAddress		0xD0

void RTC_Init(void);
void RTC_WriteData(unsigned char dataRegister, char data);
unsigned char RTC_ReadData(unsigned char dataRegister);
void RTC_SetSQWOutput(int Hz);
char RTC_bcdToDec(char val);
char RTC_decToBcd(char val);
void RTC_setTime(unsigned char min, unsigned char hour);
void RTC_SetAlarmTime(char number, int posAlarmTime);
void RTC_printTime(unsigned char min, unsigned char hour);
unsigned char RTC_getMinuts(void);
unsigned char RTC_getHours(void);
unsigned char RTC_getAlarmMinuts(void);
unsigned char RTC_getAlarmHours(void);

#endif
