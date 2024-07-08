#include "ftrans.h"

#include <math.h>
#include "../utils/alloc.h"

void dft(WAVFile *wavfile, dcomplex* output) {
    const int nrSamples = NR_SAMPS(wavfile);
    for (int k = 0; k < nrSamples; k++) {
        dcomplex sum = .0 * I;
        for (int n = 0; n < nrSamples; n++) {
            const double angle = 2. * M_PI * k * n / nrSamples;
            sum += wavfile->buffer[n] * cexp(-I * angle);
        }
        output[k] = sum;
    }
} 

void fft(dcomplex *input, int nrSamples) {
    if (nrSamples <= 1) {
        return;
    }
    dcomplex *even = (dcomplex*)ehCalloc(nrSamples/2, sizeof(dcomplex));
    dcomplex *odd = (dcomplex*)ehCalloc(nrSamples/2, sizeof(dcomplex));

    for (int i = 0; i < nrSamples/2; i++) {
        even[i] = input[i*2];
        odd[i] = input[i*2 + 1];
    }

    fft(even, nrSamples/2);
    fft(odd, nrSamples/2);

    for (int k = 0; k < nrSamples/2; k++) {
        dcomplex t = cexp(-2. * I * M_PI * k / nrSamples) * odd[k];
        input[k] = even[k] + t;
        input[k + nrSamples/2] = even[k] - t;
    }

    free(even);
    free(odd);
}

dcomplex *performFT(WAVFile *wavfile) {
    const int ALLOWED_LIM = 100;
    const int nrSamples = NR_SAMPS(wavfile);
    dcomplex *output = (dcomplex*)ehCalloc(nrSamples, sizeof(dcomplex));
    if (nrSamples <= ALLOWED_LIM) {
        dft(wavfile, output);
    } else {
        for (int i = 0; i < nrSamples; i++) {
            output[i] = wavfile->buffer[i];
        }
        fft(output, nrSamples);
    }
    return output;
}

