#include "logvol.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>

void logvol(WAVFile *wavfile, int gain) {
    double gainFactor = pow(10.0, gain / 20.0);
    printf("Gain factor: %f\n", gainFactor);

    uint32_t numSamples = wavfile->header.subchunk2Size / (wavfile->header.bitsPerSample / 8);
    printf("Number of samples: %u\n", numSamples);

    for (uint32_t i = 0; i < numSamples; i++) {
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

        // Debug print to track sample values
        if (i < 10) { // Print only the first few samples for brevity
            printf("Sample %u: Original: %d, Scaled: %d\n", 
                   i, originalSample, (int32_t)scaledSample);
        }
    }
}

