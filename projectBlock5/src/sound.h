
#ifndef SOUND_H_
#define SOUND_H_

#include "soundFiles.h"

#define PWM_CHANNEL 	1
#define PWM_RESOLUTION	300
#define SAMPLE_TIMER	TIMER0
#define VOLUME_IOPORT	PORT2
#define ALL_PINS		0x1C
#define VOLUME1_PIN		1 << 2
#define VOLUME2_PIN		1 << 3
#define VOLUME3_PIN		1 << 4

void sound_Init(void);
void sound_Select(audioFile *file, short speed);
void sound_Play(void);
void sound_Pauze(void);
void sound_SetVolume(unsigned char volume);

#endif
