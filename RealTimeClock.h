#define RTC_Secondes_Register  	0x00
#define RTC_Minuten_Register   	0x01
#define RTC_Hours_Register 	  	0x02
#define RTC_Day_Register 		0x03
#define RTC_Date_Register 	  	0x04
#define RTC_Month_Register   	0x05
#define RTC_Year_Register   	0x06
#define RTC_Control_Register   	0x07
#define RTC_SlaveAddress		0xD0

#define IR			(*(unsigned int *)	0x40090000)
#define CTCR		(*(unsigned int *)	0x40090070)

#define MR02		(*(unsigned int *)	0x40090018)
#define TCR			(*(unsigned int *)	0x40090004)
#define PCTIM2		(*(unsigned int *)	0x400FC0C4)

#define CR			(*(unsigned int *)	0x40090004)
#define CCR			(*(unsigned int *)	0x40090028)
#define PCLKSEL1	(*(unsigned int *)	0x400FC1AC)
#define ISER0		(*(unsigned int *)	0xE000E100)
#define T2PR		(*(unsigned int *)	0x4009000C)


void RTC_Init(char seconde, char minute, char hour);
void RTC_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data);
unsigned char RTC_ReadData(unsigned char slaveAddress, unsigned char dataRegister);
unsigned char RTC_GetMinutes();
unsigned char RTC_GetHours();
void RTC_SetSQWOutput(int Hz);
char bcdToDec(char val);
char decToBcd(char val);
