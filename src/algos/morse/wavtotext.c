#include "wavtotxt.h"

#include <math.h>

const int SPACE_LIM = 3e4;
const int LET_SEP_LIM = 13e3;
const int LINE_LIM = 13e3;
const int DOT_LIM = 5e3;

const int PROC_DISP_INT = 1e4;

string *wavToTxt(WAVFile *wavfile) {
    string *morseTxt = str_create("");
    int nr = 0, nr0 = 0;
    const int nrSamps = NR_SAMPS(wavfile);
    for (int i = 0; i < nrSamps; i++) {
        if (i % PROC_DISP_INT == 0) {
            printf("%.2f%%\n", 100.f * i / nrSamps);
        }
        const int32_t sample = wavfile->buffer[i];

        if (sample == 0) {
            nr0++;
        } else {
            if (nr0 > SPACE_LIM) {
                str_append(morseTxt, " / ");
            }
            if (nr0 > LET_SEP_LIM) {
                str_cappend(morseTxt, ' ');
            }
            nr0 = 0;
        }

        if (sample != 0) {
            nr++;
        } else {
            if (nr != 0) {
                if (nr > LINE_LIM) {
                    str_cappend(morseTxt, '-');
                }
                if (nr < DOT_LIM) {
                    str_cappend(morseTxt, '.');
                }
            }
            nr = 0;
        }
    }
    
    return morseTxt;
}