#include "timer.h"
#include "GPIO.h"

unsigned char pwmDir = 1;
float pwmDutycycle = 0;
float oscillationSpeed = 0.1;

void sound_Init(short freq){
	GPIO_SetDIR(VOLUME_IOPORT,ALL_PINS);

	timer_Init(PWM,0);
	timer_SetMR(PWM,MR0,RESOLUTION);
	timer_SetMCR(PWM,MR0,0x2);
	timer_SetMCR(PWM,MR1,0x3);
	timer_EnablePWM(1);
}

void sound_SetFrequency(short freq){
	oscillationSpeed = RESOLUTION*2 / ((CPU_F / RESOLUTION) / freq);
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

void PWM1_IRQHandler(void){
	timer_ClearIR(PWM);

	pwmDutycycle+= oscillationSpeed * pwmDir;
	timer_SetPWMMR(MR1,(int) (pwmDutycycle - 0.5));

	if(pwmDutycycle == 0.0 || pwmDutycycle == 10.0)
		pwmDir *= -1;
}
