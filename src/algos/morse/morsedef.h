#ifndef __MORSEDEF_H
#define __MORSEDEF_H

#include "./../../libs/string.h"


#define MAX_CODE_LEN 10

string *morseToText(const char *const morseCode);

#endif