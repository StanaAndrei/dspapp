#ifndef __DELAYEFFS_H
#define __DELAYEFFS_H

#include "../utils/wav.h"

#define GAIN .5
#define GAIN_FB .75

void addEcho(WAVFile *wavfile, int circularBuffSize);

#endif