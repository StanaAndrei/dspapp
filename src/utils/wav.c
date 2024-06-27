#include "wav.h"
#include "file.h"

void readWavFile(WAVFile *wavfile, const char path[]) {
    FILE *f = openFile(path, "rb");

    fread(&wavfile->header, sizeof(WAVHeader), 1, f);
    const uint32_t subchunk2Size = wavfile->header.subchunk2Size;
    wavfile->buffer = (BYTE*)calloc(subchunk2Size, sizeof(BYTE));
    fread(wavfile->buffer, sizeof(BYTE), subchunk2Size, f);

    closeFile(f);
}