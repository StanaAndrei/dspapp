#ifndef __MORSEDEF_H
#define __MORSEDEF_H

#include "./../../libs/string.h"


extern const char* morseAlphabet[];
extern const char* morseDigits[];

#define MAX_CODE_LEN 10

string *morseToText(const char *const morseCode);

#endif