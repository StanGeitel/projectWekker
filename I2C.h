#ifndef I2C1_H_
#define I2C1_H_

#define I2C1CONSET  (*(unsigned int *)	0x4005C000) // Control Set Register
#define I2C1DAT  	(*(unsigned int *)	0x4005C008) // data register
#define I2C1CONCLR  (*(unsigned int *)	0x4005C018) // clear control register
#define I2C1SCLH  	(*(unsigned int *)	0x4005C010) // SCH Duty Cycle Register High Half Word
#define I2C1SCLL  	(*(unsigned int *)	0x4005C014) // SCL Duty Cycle Register Low Half Word
#define PINSEL0  	(*(unsigned int *)	0x4002C000) // Pinselect register
#define I2C1STAT  	(*(unsigned int *)	0x4005C004) // status register
#define PCONP  		(*(unsigned int *)	0x400FC0C4) // Power register
#define PCLKSEL1  	(*(unsigned int *)	0x400FC1AC)

#define I2C_Conset_AA		0x04
#define I2C_Conset_SI		0x08
#define I2C_Conset_STO		0x10
#define I2C_Conset_STA		0x20
#define I2C_Conset_I2EN		0x40
#define I2C_Conclr_AAC		0x04
#define I2C_Conclr_SIC		0x08
#define I2C_Conclr_STAC		0x20
#define I2C_Conclr_I2ENC`	0x40


void I2C_Init();
void I2C_SendStartBit();
void I2C_SendStopBit();
void I2C_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data);
unsigned char I2C_ReadData(unsigned char slaveAddress, unsigned char dataRegister);
void I2C_SelectRegister(unsigned char slaveAddress, unsigned char dataRegister);


#endif /* I2C1_H_ */
