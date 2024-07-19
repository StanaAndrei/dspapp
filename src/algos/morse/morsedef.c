#include "morsedef.h"

#include "./../../utils/utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char* morseAlphabet[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", 
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", 
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};

const char* morseDigits[] = {
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

#define ALPHA_SIZE ('z' - 'a' + 1)
const char ALPHABET[ALPHA_SIZE + 1] = "abcdefghijklmnopqrstuvwxyz";

#define NR_DIGITS 10
const char DIGITS[NR_DIGITS + 1] = "01234546789";

char tokenToChar(const char token[MAX_CODE_LEN]) {
    for (int i = 0; i < ALPHA_SIZE; i++) {
        if (!strcmp(token, morseAlphabet[i])) {
            return ALPHABET[i];
        }
    }
    for (int i = 0; i < NR_DIGITS; i++) {
        if (!strcmp(token, morseDigits[i])) {
            return DIGITS[i];
        }
    }
    return -1;
}

char *morseToText(const char *const morseCode) {
    const char *DELIM = " /";
    char *auxCode = ehStrdup(morseCode);
    char *token = strtok(auxCode, DELIM);
    while (token != NULL) {
        //putchar(tokenToChar(token));
        token = strtok(NULL, DELIM);
    }
    free(auxCode);
}