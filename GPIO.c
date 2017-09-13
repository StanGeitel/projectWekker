#include "LPC1769.h"


void GPIO_Init(unsigned char port, int DIR,int pins){
	GPIO_DIR(port) = DIR;
}

void GPIO_Int_Init(void){
	ISER0 |= 1 << 21;		//enable external interrupt 3
	PCLKSEL1 |= (1 << 2);		//select clock for GPIO interrupt
}

void GPIO_Set(unsigned char port, int pins){
	GPIO_SET(port) = pins;
}

void GPIO_Clear(unsigned char port, int pins){
	GPIO_CLR(port) = pins;
}

void GPIO_Toggle(unsigned char port, int pins){
	GPIO_PIN(port) ^= pins;
}

int GPIO_Read(unsigned char port){
	return GPIO_PIN(port);
}

void GPIO_Int_Clear(unsigned char port, int pins){
	GPIO_IntClt(port) |= pins & port? GPIO2_IntPins : GPIO0_IntPins;
}

void GPIO_Int_EnableR(unsigned char port, int pins){
	GPIO_IntEnR(port) &= ~port? GPIO2_IntPins : GPIO0_IntPins;
	GPIO_IntEnR(port) |= pins & port? GPIO2_IntPins : GPIO0_IntPins;
}

void GPIO_Int_EnableF(unsigned char port, int pins){
	GPIO_IntEnR(port) &= ~port? GPIO2_IntPins : GPIO0_IntPins;
	GPIO_IntEnF(port) |= pins & port? GPIO2_IntPins : GPIO0_IntPins;
}

int GPIO_Int_StatusR(unsigned char port, int pins){
	return GPIO_IntStatR(port) & port? GPIO2_IntPins : GPIO0_IntPins;
}

int GPIO_Int_StatusF(unsigned char port, int pins){
	return GPIO_IntStatF(port) & port? GPIO2_IntPins : GPIO0_IntPins;
}

