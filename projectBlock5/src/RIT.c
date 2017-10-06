#include "LPC1769.h"

void RIT_Init(void){
	PCONP |= 1 << 16;
	PCLKSEL1 |= 1 << 26;
	ISER0 |= 1 << 29;
	RIT_CTRL |= 0x3;

}

void RIT_ClearIR(void){
	RIT_CTRL |= 1;
}

void RIT_Enable(void){
	RIT_CTRL |= 1 << 3;
}

void RIT_Disable(void){
	RIT_CTRL &= ~(1 << 3);
}

void RIT_SetCOMP(int value){
	RIT_COMP = value;
}

void RIT_GetCount(){
	return RIT_COUNTER;
}
