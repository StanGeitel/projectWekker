#include "timer.h"
#include "GPIO.h"
#include "sound.h"

signed char pwmDir = 1;
float pwmDutycycle = 0;
float oscillationSpeed = 0.1;

void sound_Init(short freq){
	GPIO_SetDIR(VOLUME_IOPORT,ALL_PINS);

	timer_Init(PWM,0);

	timer_SetMCR(PWM,MR3,0x0);
	timer_PWM_SetMR(MR3,150);

	timer_PWM_SetMR(MR0,300);
	timer_PWM_SetMR(MR2,150);
	timer_SetMCR(PWM,MR0,0x3);
	timer_SetMCR(PWM,MR2,0x0);
	timer_PWM_Enable(0x6);
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

	pwmDutycycle+= 0.004 * pwmDir;
	timer_PWM_SetMR(MR2, (int) (pwmDutycycle - 0.5));
	timer_PWM_SetMR(MR3, (int) (pwmDutycycle - 0.5));


	if(pwmDutycycle <= -0.0 || pwmDutycycle >= 300.0)
		pwmDir *= -1;
}
