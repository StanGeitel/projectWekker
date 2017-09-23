void RTC_Init();
void RTC_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data);
unsigned char RTC_ReadData(unsigned char slaveAddress, unsigned char dataRegister);
unsigned char RTC_GetMinutes();
unsigned char RTC_GetHours();
void RTC_SetSQWOutput(int Hz);
