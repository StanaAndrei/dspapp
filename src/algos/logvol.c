#include "logvol.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>

void logvol(WAVFile *wavfile, int gain) {
    double gainFactor = pow(10.0, gain / 20.0);
    for (uint32_t i = 0; i < NR_SAMPS(wavfile); i++) {
        int32_t originalSample = wavfile->buffer[i];
        double scaledSample = (double)originalSample * gainFactor;
        scaledSample = clipSample(1. * scaledSample);
        wavfile->buffer[i] = (int32_t)scaledSample;
    }
}

