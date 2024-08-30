#ifndef __WAVTOTXT_H
#define __WAVTOTXT_H

#include "../../utils/utils.h"
#include "../../libs/dynstr.h"

DynStr wavToTxt(WAVFile *wavfile);

#endif