#include "LPC1769.h"

void SPI_Init(void){
	PIN_SEL0 = 1 << 31;
	PIN_SEL1 = 1 << 5;

	PCONP |= 1 << 21;
	PCLKSEL1 |= 1 << 10;
	ISER0 |= 1 << 14;

	SSP_CPSR &= ~0xFF;
	SSP_CR0 &= ~0xFFFF;
	SSP_CR1 &= ~0xF;

	SSP_CPSR |= 0x2;
	SSP_CR0 |= 0xF;
	SSP_CR1 |= 0x2;
}

void SPI_WriteInteger(int data){
	PIN_SEL1 &= 1 << 1;
	SSP_DR = (short) data >> 16;
	SSP_DR = (short) data;
	while(!(SSP_SR & 1));
	PIN_SEL1 |= 1 << 1;
}
