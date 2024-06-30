#ifndef __DELAYEFFS_H
#define __DELAYEFFS_H

#include "../utils/wav.h"

#define GAIN .8
#define GAIN_FB .75
#define MOD_FREQ 20.

void addEcho(WAVFile *wavfile, int circularBuffSize);
void addFlanger(WAVFile *wavfile, int minBuffSize, int maxBuffSize, double modDepth);

#endif