void I2C_Init(void);
void I2C_SendStartBit();
void I2C_SendStopBit();
void I2C_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data);
unsigned char I2C_ReadData(unsigned char slaveAddress, unsigned char dataRegister);
void I2C_WaitForSIAndReset();
