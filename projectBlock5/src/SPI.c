#include "LPC1769.h"

void SPI_Init(void){
	PCONP |= 1 << 21;
	PCLKSEL1 |= 1 << 10;
	ISER0 |= 1 << 14;

	SSP_CPSR |= 0x2;
	SSP_CR0 |= 0xF;
	SSP_CR1 |= 0x2;
}

void SPI_WriteInteger(int data){
	PIN_SEL1 &= ~1 << 1;							//set slave select as GPIO(this is pin then becomes low see 'display.c::21'
	SSP_DR |= (data >> 16) & 0xFFFF;				//write last 16 data bit to FIFO, because SPI is MSB first
	SSP_DR |= data & 0xFFFF;						//write first 16 data bit to FIFO
	while(!(SSP_SR & 1));							//wait until FIFO is empty to make sure the first 16 bits have been send and the last 16 bits have been copied to the SSP shift register
	PIN_SEL1 |= 1 << 1;								//set slave select as SSEL pin that stays LOW until end of transmission
}
