#ifndef __FTRANS_H
#define __FTRANS_H

#include "../utils/wav.h"
#include <complex.h>
typedef double complex dcomplex;

dcomplex* performFT(WAVFile *wavfile);

#endif