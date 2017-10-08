
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
#define RTC_SlaveAddress		0xD0

#define RTC_TIMER TIMER3

#define TIMER TIMER0

void RTC_TimerInit();
void RTC_Init(char seconde, char minute, char hour);
void RTC_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data);
unsigned char RTC_ReadData(unsigned char slaveAddress, unsigned char dataRegister);
unsigned char RTC_GetMinutes();
unsigned char RTC_GetHours();
void RTC_SetSQWOutput(int Hz);
char RTC_bcdToDec(char val);
char RTC_decToBcd(char val);
void RTC_setTime(int min, int hour);
char* RTC_getTime();


#endif
