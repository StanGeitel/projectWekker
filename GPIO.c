#include "LPC1769.h"

<<<<<<< HEAD
=======
void GPIO_Init(unsigned char port, int DIR,int pins){
	GPIO_DIR(port) = DIR;
}
>>>>>>> 49824f6e8ade104739feac0e5ebaf2843d7c976f

void GPIO_Int_Init(void){
	ISER0 |= 1 << 21;		//enable external interrupt 3
	GPIO_Int_Clear(PORT0,0xFFF);
}

void GPIO_SetDIR(unsigned char port, int pins){
	GPIO_DIR(port) = pins;
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

void GPIO_Int_ClearFlag(unsigned char port, int pins){
	GPIO_IntClt(port) |= pins & port? GPIO2_IntPins : GPIO0_IntPins;
}

unsigned char GPIO_Int_Status(){
	return (GPIO_IntStatus >> 1) + (GPIO_IntStatus & 1);	//return bit 0 and 2 as bit 0 and 1
}

void GPIO_Int_EnableR(unsigned char port, int pins){
	GPIO_IntEnR(port) |= pins & (port? GPIO2_IntPins : GPIO0_IntPins);
}

void GPIO_Int_EnableF(unsigned char port, int pins){
	GPIO_IntEnF(port) |= pins & (port? GPIO2_IntPins : GPIO0_IntPins);
}

void GPIO_Int_DisableR(unsigned char port, int pins){
	GPIO_IntEnR(port) &= ~(pins & port? GPIO2_IntPins : GPIO0_IntPins);
}

void GPIO_Int_DisableF(unsigned char port, int pins){
	GPIO_IntEnF(port) &= ~(pins & port? GPIO2_IntPins : GPIO0_IntPins);
}

int GPIO_Int_StatusR(unsigned char port){
	return GPIO_IntStatR(port) & (port? GPIO2_IntPins : GPIO0_IntPins);
}

int GPIO_Int_StatusF(unsigned char port){
	return GPIO_IntStatF(port) & (port? GPIO2_IntPins : GPIO0_IntPins);
}

