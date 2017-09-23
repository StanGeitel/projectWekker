/*
 * I2C.h
 *
 *  Created on: 23 Sep 2017
 *      Author: stan
 */

#ifndef I2C_H_
#define I2C_H_

#include "LPC1769.h"

#define I2C0CONSET  (*(unsigned int *)	0x4001C000) // Control Set Register
#define I2C0DAT  	(*(unsigned int *)	0x4001C008) // dataregister
#define I2C0CONCLR  (*(unsigned int *)	0x4001C018) // clear control register
#define I2C0SCLH  	(*(unsigned int *)	0x4001C010) // SCH Duty Cycle Register High Half Word
#define I2C0SCLL  	(*(unsigned int *)	0x4001C014) // SCL Duty Cycle Register Low Half Word
#define PINSEL1  	(*(unsigned int *)	0x4002C004) // Pinselect register
#define I2C0STAT  	(*(unsigned int *)	0x4001C004) // I2C status register

void I2C_Init(void);
void I2C_SendStartBit();
void I2C_SendStopBit();
void I2C_WriteData(unsigned char slaveAddress, unsigned char dataRegister, unsigned char data);
unsigned char I2C_ReadData(unsigned char slaveAddress, unsigned char dataRegister);
void I2C_WaitForSIAndReset();

#endif /* I2C_H_ */
