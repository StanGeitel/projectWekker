
#ifndef SOUND_H_
#define SOUND_H_

#define VOLUME_IOPORT	PORT2
#define ALL_PINS		0x1C
#define VOLUME1_PIN		1 << 2
#define VOLUME2_PIN		1 << 3
#define VOLUME3_PIN		1 << 4
#define RESOLUTION		10
#define CPU_F			4000000

void sound_SetVolume(unsigned char volume);
void sound_SetFrequency(short freq);
void sound_Init(short freq);

#endif
