#ifndef __MORSEDEF_H
#define __MORSEDEF_H

#include "./../../libs/dynstr.h"

#include <stdlib.h>

extern const char* morseAlphabet[];
extern const char* morseDigits[];
extern const int SPACE_LIM;
extern const int LET_SEP_LIM;
extern const int LINE_LIM;
extern const int DOT_LIM;

#define MAX_CODE_LEN 10

DynStr morseToText(const char *const morseCode);
DynStr textToMorse(const char *const text);
void playMorse(const char *const morseCode);

static inline void playDot() { system("play -nq -t alsa synth 0.2 sine 1000"); }
static inline void playLine() { system("play -nq -t alsa synth 0.6 sine 1000"); }

#endif
