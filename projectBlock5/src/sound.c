#include "LPC1769.h"
#include "timer.h"
#include "GPIO.h"
#include "sound.h"

int dataOffset;
audioFile *file;

void sound_Init(void){
	GPIO_SetDIR(VOLUME_IOPORT,ALL_PINS);

	timer_Init(PWM,0);
	timer_PWM_SetMR(MR0,PWM_RESOLUTION);
	timer_PWM_SetMR(PWM_CHANNEL,0);
	timer_SetMCR(PWM,MR0,0x2);
	timer_SetMCR(PWM,PWM_CHANNEL,0x0);
	timer_PWM_Enable(PWM_CHANNEL);

	timer_Init(SAMPLE_TIMER,0);
	timer_SetMR(SAMPLE_TIMER,MR0,1);
	timer_SetMCR(SAMPLE_TIMER,MR0,0x3);
}

void sound_Select(audioFile *newFile, short speed){
	file = newFile;
	timer_SetPR(SAMPLE_TIMER, 10884 );
}

void sound_Play(void){
	timer_Enable(SAMPLE_TIMER);
}

void sound_Pauze(void){
	timer_Disable(SAMPLE_TIMER);
	timer_PWM_SetMR(PWM_CHANNEL, 0);
}

void sound_SetVolume(unsigned char volume){
	GPIO_Clear(VOLUME_IOPORT,ALL_PINS);
	switch(volume){
	case 1:
		GPIO_Set(VOLUME_IOPORT,VOLUME1_PIN);
		break;
	case 2:
		GPIO_Set(VOLUME_IOPORT,VOLUME2_PIN);
		break;
	case 3:
		GPIO_Set(VOLUME_IOPORT,VOLUME3_PIN);
		break;
	}
}

void TIMER0_IRQHandler(void){
 	timer_ClearIR(SAMPLE_TIMER);

	timer_PWM_SetMR(PWM_CHANNEL,(int) ((float) file->data[dataOffset] * 1.17647 + 0.5));
	dataOffset == file->size - 1 ? dataOffset = 0 : dataOffset++;
}
