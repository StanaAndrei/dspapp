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

void writeWavFile(const WAVFile *const wavfile, const char path[]) {
    FILE *fout = openFile(path, "wb");
    fwrite(&wavfile->header, sizeof(WAVHeader), 1, fout);
    fwrite(wavfile->buffer, sizeof(BYTE), wavfile->header.dsz, fout);
    closeFile(fout);//*/
}