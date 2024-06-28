#include "wav.h"
#include "file.h"
#include "alloc.h"
#include <string.h>

void readWavFile(WAVFile *wavfile, const char path[]) {
    FILE *f = openFile(path, "rb");

    fread(&wavfile->header, sizeof(WAVHeader), 1, f);
    const uint32_t subchunk2Size = wavfile->header.subchunk2Size;
    const uint16_t bitsPerSample = wavfile->header.bitsPerSample;
    const int numSamples = subchunk2Size / (bitsPerSample / 8);

    // Allocate buffer for normalized 32-bit samples
    wavfile->buffer = (uint32_t*)ehCalloc(numSamples, sizeof(uint32_t));

    // Read the original data into a temporary buffer
    BYTE *originalBuffer = (BYTE*)ehCalloc(subchunk2Size, sizeof(BYTE));
    fread(originalBuffer, sizeof(BYTE), subchunk2Size, f);

    // Convert samples to 32-bit normalized integers
    for (int i = 0; i < numSamples; i++) {
        int32_t sampleValue = 0;

        if (bitsPerSample == 8) {
            // Convert 8-bit unsigned to 32-bit signed
            sampleValue = (int32_t)(originalBuffer[i] - 128) << 24; // Center and scale
        } else if (bitsPerSample == 16) {
            // Convert 16-bit signed to 32-bit signed
            sampleValue = (int32_t)(*((int16_t *)(originalBuffer + i * 2))) << 16;
        } else if (bitsPerSample == 24) {
            // Convert 24-bit signed to 32-bit signed
            sampleValue = (int32_t)(originalBuffer[i * 3] |
                                    (originalBuffer[i * 3 + 1] << 8) |
                                    (originalBuffer[i * 3 + 2] << 16)) << 8;
        } else if (bitsPerSample == 32) {
            // Directly use 32-bit signed
            sampleValue = *((int32_t *)(originalBuffer + i * 4));
        }

        // Store the sample as 32-bit integer
        wavfile->buffer[i] = sampleValue;
    }

    free(originalBuffer);
    closeFile(f);
}

void writeWavFile(const WAVFile *const wavfile, const char path[]) {
    FILE *fout = openFile(path, "wb");
    fwrite(&wavfile->header, sizeof(WAVHeader), 1, fout);

    const uint32_t subchunk2Size = wavfile->header.subchunk2Size;
    const uint16_t bitsPerSample = wavfile->header.bitsPerSample;
    const int numSamples = subchunk2Size / (bitsPerSample / 8);

    BYTE *outputBuffer = (BYTE*)ehCalloc(subchunk2Size, sizeof(BYTE));

    for (int i = 0; i < numSamples; i++) {
        int32_t sampleValue = wavfile->buffer[i];

        if (bitsPerSample == 8) {
            // Convert 32-bit signed to 8-bit unsigned range
            outputBuffer[i] = (BYTE)((sampleValue >> 24) + 128); // Convert to unsigned
        } else if (bitsPerSample == 16) {
            // Convert 32-bit signed to 16-bit signed range
            int16_t scaledSample = (int16_t)(sampleValue >> 16); // Scale down to 16-bit
            memcpy(outputBuffer + i * 2, &scaledSample, sizeof(int16_t));
        } else if (bitsPerSample == 24) {
            // Convert 32-bit signed to 24-bit signed range
            int32_t scaledSample = sampleValue >> 8; // Scale down to 24-bit
            outputBuffer[i * 3] = scaledSample & 0xFF;
            outputBuffer[i * 3 + 1] = (scaledSample >> 8) & 0xFF;
            outputBuffer[i * 3 + 2] = (scaledSample >> 16) & 0xFF;
        } else if (bitsPerSample == 32) {
            // Directly use 32-bit signed
            memcpy(outputBuffer + i * 4, &sampleValue, sizeof(int32_t));
        }
    }

    fwrite(outputBuffer, sizeof(BYTE), subchunk2Size, fout);
    free(outputBuffer);
    closeFile(fout);
}

int64_t clipSample(int64_t sample) {
    if (sample > INT32_MAX) {
        return INT32_MAX;
    }
    if (sample < INT32_MIN) {
        return INT32_MIN;
    }
    return (int32_t)sample;
}
