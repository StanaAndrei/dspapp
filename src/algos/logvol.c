#include "logvol.h"
#include <math.h>
#include <limits.h>

void logvol(WAVFile *wavfile, int gain) {
    // Calculate the gain factor
    double gainFactor = pow(10., gain / 20.);

    // Determine sample size in bytes
    int sampleSize = wavfile->header.bitsPerSample / 8;
    int numSamples = wavfile->header.subchunk2Size / sampleSize;

    for (uint32_t i = 0; i < numSamples; i++) {
        if (sampleSize == 1) { // 8-bit audio, unsigned
            uint8_t *sample = (uint8_t *)(wavfile->buffer + i * sampleSize);
            int32_t scaledSample = (int32_t)((*sample - (INT8_MAX + 1)) * gainFactor + (INT8_MAX + 1)); // Center around SCHAR_MAX

            // Clip to prevent overflow
            if (scaledSample > UINT8_MAX) {
                scaledSample = UINT8_MAX;
            } else if (scaledSample < 0) {
                scaledSample = 0;
            }

            *sample = (uint8_t)scaledSample;
        } else if (sampleSize == 2) { // 16-bit audio, signed
            int16_t *sample = (int16_t *)(wavfile->buffer + i * sampleSize);
            int32_t scaledSample = (int32_t)(*sample * gainFactor);

            // Clip to prevent overflow
            if (scaledSample > INT16_MAX) {
                scaledSample = INT16_MAX;
            } else if (scaledSample < INT16_MIN) {
                scaledSample = INT16_MIN;
            }

            *sample = (int16_t)scaledSample;
        } else if (sampleSize == 3) { // 24-bit audio, signed
            // Read three bytes and assemble into a 24-bit signed integer
            uint8_t *sample = (uint8_t *)(wavfile->buffer + i * sampleSize);
            int32_t sample24 = sample[0] | (sample[1] << 8) | (sample[2] << 16);

            // Adjust for 24-bit signed value
            if (sample24 & 0x800000) {
                sample24 |= ~0xFFFFFF; // Sign extend if negative
            }

            int64_t scaledSample = (int64_t)(sample24 * gainFactor);

            // Clip to prevent overflow
            if (scaledSample > 0x7FFFFF) {
                scaledSample = 0x7FFFFF;
            } else if (scaledSample < -0x800000) {
                scaledSample = -0x800000;
            }

            // Store back as three bytes
            sample[0] = scaledSample & 0xFF;
            sample[1] = (scaledSample >> 8) & 0xFF;
            sample[2] = (scaledSample >> 16) & 0xFF;
        } else if (sampleSize == 4) { // 32-bit audio, signed
            int32_t *sample = (int32_t *)(wavfile->buffer + i * sampleSize);
            int64_t scaledSample = (int64_t)(*sample * gainFactor);

            // Clip to prevent overflow
            if (scaledSample > INT32_MAX) {
                scaledSample = INT32_MAX;
            } else if (scaledSample < INT32_MIN) {
                scaledSample = INT32_MIN;
            }

            *sample = (int32_t)scaledSample;
        }
    }
}