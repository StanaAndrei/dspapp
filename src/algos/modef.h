#ifndef __MODEF_H
#define __MODEF_H

#include "../utils/wav.h"

void ringMod(WAVFile *wavfile, double modFreq);
void tremolo(WAVFile *wavfile, double modFreq, double modAmpl);

#endif