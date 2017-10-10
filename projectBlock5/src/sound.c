#include "LPC1769.h"
#include "timer.h"
#include "GPIO.h"
#include "sound.h"

float volume = 0.5;
int dataOffset;
audioFile *file;

void sound_Init(void){
	GPIO_SetDIR(AMP_IOPORT,AMP_PINS);
	GPIO_Set(AMP_IOPORT,AMP_PINS);

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
	dataOffset = 0;
	timer_SetPR(SAMPLE_TIMER, CPU_FREQ/ file->sampleRate/speed );
}

void sound_Play(void){
	timer_Enable(SAMPLE_TIMER);
}

void sound_Pauze(void){
	timer_Disable(SAMPLE_TIMER);
	timer_PWM_SetMR(PWM_CHANNEL, 0);
}

void sound_SetAmplefier(unsigned char amp){
	GPIO_Set(AMP_IOPORT,AMP_PINS);
	switch(amp){
	case 1:
		GPIO_Clear(AMP_IOPORT,AMP1_PIN);
		break;
	case 2:
		GPIO_Clear(AMP_IOPORT,AMP2_PIN);
		break;
	case 3:
		GPIO_Clear(AMP_IOPORT,AMP3_PIN);
		break;
	}
}

void sound_IncreaseVolume(void){
	volumE += 0.1;
}

void sound_DecreaseVolume(void){
	volumE += 0.1;
}

void TIMER0_IRQHandler(void){
 	timer_ClearIR(SAMPLE_TIMER);

 	float data = file->data[dataOffset];
 	data -= 127;
 	data *= volume;	//increase amplitude
 	data += 127;

 	//dial back the volumE if data starts clipping
 	if(data < 0){
 		volume -= (0 - data) / 127.0;
 	}else if(data > PWM_RESOLUTION){
 		volume -= (data - PWM_RESOLUTION) / 127.0;
 	}

	timer_PWM_SetMR(PWM_CHANNEL, file->data[dataOffset]);
 	dataOffset == file->size - 1 ? dataOffset = 0 : dataOffset++;
}
