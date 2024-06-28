#include "modef.h"
#include "../utils/alloc.h"
#include <math.h>
#define _USE_MATH_DEFINES


void ringMod(WAVFile *wavfile, double modFreq) {
    for (int i = 0; i < NR_SAMPS(wavfile); i++) {
        const double timeI = 1. * (i - 1) / wavfile->header.sampleRate;
        int64_t scaledSample = 1. * wavfile->buffer[i] * sin(2. * M_PI * modFreq * timeI);
        scaledSample = clipSample(scaledSample);
        wavfile->buffer[i] = (int32_t)scaledSample;
    }
}

void tremolo(WAVFile *wavfile, double modFreq, double modAmpl) {
    double sampleRate = (double)wavfile->header.sampleRate;

    for (int i = 0; i < NR_SAMPS(wavfile); i++) {
        double carrier = 1. + modAmpl * sin(2. * M_PI * modFreq * i / sampleRate);
        int64_t scaledSample = (int64_t)((double)wavfile->buffer[i] * carrier);
        scaledSample = clipSample(scaledSample);
        wavfile->buffer[i] = (int32_t)scaledSample;
    }
}

