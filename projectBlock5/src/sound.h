
#ifndef SOUND_H_
#define SOUND_H_

#include "soundFiles.h"

#define PWM_CHANNEL 		2
#define PWM_RESOLUTION		300
#define SAMPLE_TIMER		TIMER0
#define AMP_IOPORT			PORT2
#define AMP_PINS			0x1C
#define AMP1_PIN			1 << 2
#define AMP2_PIN			1 << 3
#define AMP3_PIN			1 << 4
#define LOOP_FILE			1 << 31

void sound_Init(void);
void sound_Select(audioFile *file, short speed, unsigned char looped);
void sound_Play(void);
void sound_Stop(void);
void sound_SetAmplefier(unsigned char amp);
void sound_IncreaseVolume(void);
void sound_DecreaseVolume(void);

#endif
