#include "LPC1769.h"

/*
void SPI_Init(){
	PCONP |= 1 << 8;
	PCLKSEL0 |= 1 << 16;
	ISER0 |= 1 << 13;

//	SPI_CCR |= 0x8;
	SPI_CR |= 0xAC;

}

void SPI_Write(short data){
	//SPI_CR &= ~0x2C;
	SPI_CR |= 0xAC;

	while(SPI_SR & (1 << 6))
		SPI_SR |= 1 << 6;
	SPI_DR |= data;
}

void SPI_Int_Clear(void){
	SPI_INT |= 1;
}
*/
