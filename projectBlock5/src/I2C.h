#ifndef I2C1_H_
#define I2C1_H_

#define I2C_Conset_AA		0x04
#define I2C_Conset_SI		0x08
#define I2C_Conset_STO		0x10
#define I2C_Conset_STA		0x20
#define I2C_Conset_I2EN		0x40
#define I2C_Conclr_AAC		0x04
#define I2C_Conclr_SIC		0x08
#define I2C_Conclr_STAC		0x20
#define I2C_Conclr_I2ENC	0x40

void I2C_Init();
void I2C_SendStartBit();
void I2C_SendStopBit();
void I2C_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data);
unsigned char I2C_ReadData(unsigned char slaveAddress, unsigned char dataRegister);
void I2C_SelectRegister(unsigned char slaveAddress, unsigned char dataRegister);


#endif
