#ifndef __MORSEDEF_H
#define __MORSEDEF_H

#include "./../../libs/string.h"


extern const char* morseAlphabet[];
extern const char* morseDigits[];
extern const int SPACE_LIM;
extern const int LET_SEP_LIM;
extern const int LINE_LIM;
extern const int DOT_LIM;

#define MAX_CODE_LEN 10

string *morseToText(const char *const morseCode);

#endif