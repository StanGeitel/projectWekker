#ifndef SOUNDFILES_H_
#define SOUNDFILES_H_

typedef struct {
	int sampleRate;
	int size;
	unsigned char data[];
}audioFile;


extern const audioFile sineWave;
extern const audioFile buzzer;
extern const audioFile airRaid;
extern const audioFile powerOff;
extern const audioFile totalySpies;

#endif
