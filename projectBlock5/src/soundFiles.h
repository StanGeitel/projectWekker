#ifndef SOUNDFILES_H_
#define SOUNDFILES_H_

typedef struct {
	int sampleRate;
	int size;
	const unsigned char data[];
}audioFile;

extern const audioFile sineWave;
extern const audioFile wakeUp;

#endif
