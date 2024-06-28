#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils/wav.h"
#include "./algos/algos.h"
#include "./utils/file.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s --<algo> <filename.wav> [algo params]\n", argv[0]);
        exit(1);
    }

    WAVFile wavfile;
    readWavFile(&wavfile, argv[2]);
    if (!strcmp(argv[1], "--vol")) {
        logvol(&wavfile, atoi(argv[3]));
    } else if (0) {
        
    } else {
        fprintf(stderr, "Invalid option!\n");
        //exit(1);
    }

    writeWavFile(&wavfile, "output.wav");
    return 0;
}