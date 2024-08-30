#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./algos/algos.h"
#include "./utils/utils.h"
#include "./libs/dynstr.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Wrong usage!\n");
        exit(1);
    }

    bool shouldOutput = true;
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
        } else {
            addFlanger(&wavfile, atoi(argv[3]), atoi(argv[4]), atof(argv[5]));
        }
    } else if (!strcmp(argv[1], "--dft")) {
        dcomplex *output = performFT(&wavfile);
        WAVFile* tmp = &wavfile;
        for (int i = 0; i < NR_SAMPS(tmp); i++) {
            printf("%d: %.5f + %.5fi\n", i, creal(output[i]), cimag(output[i]));
        }
        shouldOutput = false;
    } else if (!strcmp(argv[1], "--morse-dec")) {
        shouldOutput = false;
        DynStr morseTxt = wavToTxt(&wavfile);
        DynStr text = morseToText(morseTxt.buffer);
        puts(text.buffer);
        free(morseTxt.buffer);
        free(text.buffer);
    }
    else {
        fprintf(stderr, "Option \"%s\" is invalid!\n", argv[1]);
    }

    if (shouldOutput) {
        writeWavFile(&wavfile, "output.wav");
    }
    free(wavfile.buffer);
    return 0;
}