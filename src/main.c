#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils/wav.h"
#include "./algos/algos.h"
#include "./utils/file.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        system("cat src/help.txt");
        exit(1);
    }

    WAVFile wavfile;
    readWavFile(&wavfile, argv[2]);
    if (!strcmp(argv[1], "--vol")) {
        logvol(&wavfile, atoi(argv[3]));
    } else if (!strcmp(argv[1], "--modulation")) {
        if (argc == 5) {
            tremolo(&wavfile, atof(argv[3]), atof(argv[4]));
        } else {
            ringMod(&wavfile, atof(argv[3]));
        }
    } else if (!strcmp(argv[1], "--delay")) {
        if (argc == 4) {
            addEcho(&wavfile, atoi(argv[3]));
        }
    }
    else {
        fprintf(stderr, "Option \"%s\" is invalid!\n", argv[1]);
        exit(1);
    }

    writeWavFile(&wavfile, "output.wav");
    return 0;
}