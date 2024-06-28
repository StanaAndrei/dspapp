#include "logvol.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>

void logvol(WAVFile *wavfile, int gain) {
    double gainFactor = pow(10.0, gain / 20.0);
    for (uint32_t i = 0; i < nrsamp(wavfile); i++) {
        int32_t originalSample = wavfile->buffer[i];

        // Apply the gain factor
        double scaledSample = (double)originalSample * gainFactor;

        // Clip the value to the 32-bit signed range
        if (scaledSample > INT32_MAX) {
            scaledSample = INT32_MAX;
        } else if (scaledSample < INT32_MIN) {
            scaledSample = INT32_MIN;
        }

        wavfile->buffer[i] = (int32_t)scaledSample;
    }
}

