/*
 * GPIO.h
 *
 *  Created on: 28 Sep 2017
 *      Author: stan
 */

#ifndef GPIO_H_
#define GPIO_H_

#define PORT0	0
#define PORT1	1
#define PORT2	2
#define PORT3	3

#define GPIO0_IntPins		0x7FFF8FFF
#define GPIO2_IntPins		0x3FF

void GPIO_Init(unsigned char port, int DIR, int pins);
void GPIO_Int_Init(void);
void GPIO_Set(unsigned char port, int pins);
void GPIO_Clear(unsigned char port, int pins);
void GPIO_Toggle(unsigned char port,int pins);
int GPIO_Read(unsigned char port);
void GPIO_Int_Clear(unsigned char port, int pins);
void GPIO_Int_EnableR(unsigned char port, int pins);
void GPIO_Int_EnableF(unsigned char port, int pins);
int GPIO_Int_StatusR(unsigned char port);
int GPIO_Int_StatusF(unsigned char port);

#endif /* GPIO_H_ */
