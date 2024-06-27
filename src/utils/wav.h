#ifndef __WAV_H
#define __WAV_H

#include <stdint.h>
typedef unsigned char BYTE;

typedef struct {
    char chunkID[4];       // "RIFF"
    uint32_t chunkSize; // file size - 8 bytes
    char format[4];        // "WAVE"
    char subchunk1ID[4];   // "fmt "
    uint32_t subchunk1Size; // PCM header size (16 for PCM)
    uint16_t audioFormat; // Audio format (1 for PCM)
    uint16_t numChannels; // Number of channels
    uint32_t sampleRate;    // Sampling rate (e.g., 44100 Hz)
    uint32_t byteRate;      // Byte rate = SampleRate * NumChannels * BitsPerSample/8
    uint16_t blockAlign;  // Block align = NumChannels * BitsPerSample/8
    uint16_t bitsPerSample; // Bits per sample
    char subchunk2ID[4];        // "data"
    uint32_t subchunk2Size; // Data size (file size - 44 bytes)
} WAVHeader;

typedef struct {
    WAVHeader header;
    BYTE *buffer;
} WAVFile;

void readWavFile(WAVFile *wavfile, const char path[]);

#endif