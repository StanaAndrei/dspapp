#include "delayeffs.h"
#include "../utils/alloc.h"
#include <math.h>

void addEcho(WAVFile *wavfile, int circularBuffSize) {
    int32_t *circularBuffer = (int32_t*)ehCalloc(circularBuffSize, sizeof(int32_t));
    int32_t *circularBuffer2 = (int32_t*)ehCalloc(circularBuffSize, sizeof(int32_t));
    int bufferIndex = 0;
    for (int i = 0; i < NR_SAMPS(wavfile); i++) {
        int32_t delayedSample = circularBuffer[bufferIndex];
        int32_t delaySample2 = circularBuffer2[bufferIndex];
        int64_t processedSample = (int64_t)(GAIN_FB * delaySample2) +
                                  wavfile->buffer[i] +
                                  (int64_t)((GAIN - GAIN_FB) * delayedSample);
        wavfile->buffer[i] = clipSample(processedSample);
        circularBuffer[bufferIndex] = circularBuffer2[bufferIndex] = wavfile->buffer[i];
        bufferIndex = (bufferIndex + 1) % circularBuffSize;
    }
    free(circularBuffer);
    free(circularBuffer2);
}

void addFlanger(WAVFile *wavfile, int minBuffSize, int maxBuffSize, double modDepth) {
    uint32_t sampleRate = wavfile->header.sampleRate;
    uint32_t numSamples = NR_SAMPS(wavfile);
    uint16_t numChannels = wavfile->header.numChannels;
    int32_t **circularBuffer = (int32_t**)allocMatrix(maxBuffSize, numChannels, sizeof(int32_t));
    int bufferIndex = 0;
    for (uint32_t i = 0; i < numSamples; i++) {
        double pt = 1 + modDepth * sin(2. * M_PI * MOD_FREQ * i / sampleRate);//the modulation parameter
        int circularBuffSize = (int)round((maxBuffSize - minBuffSize) * pt + minBuffSize);
        if (circularBuffSize > maxBuffSize) {
            circularBuffSize = maxBuffSize;
        }
        if (circularBuffSize < minBuffSize) {
            circularBuffSize = minBuffSize;
        }
        for (uint32_t j = 0; j < numChannels; j++) {
            int32_t delayedSample = circularBuffer[bufferIndex][j];
            int64_t processedSample = (int64_t)wavfile->buffer[i * numChannels + j];
            processedSample += (int64_t)(GAIN * delayedSample);
            processedSample = clipSample(processedSample);
            wavfile->buffer[i * numChannels + j] = circularBuffer[bufferIndex][j] = processedSample;
        }
        bufferIndex = (bufferIndex + 1) % circularBuffSize;
    }
    freeMatrix((void**)circularBuffer, (size_t)maxBuffSize);
}