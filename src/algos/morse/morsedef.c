#include "morsedef.h"

#include "./../../utils/utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>

const char* morseAlphabet[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", 
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", 
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};

const char* morseDigits[] = {
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

const int SPACE_LIM = 3e4;
const int LET_SEP_LIM = 13e3;
const int LINE_LIM = 13e3;
const int DOT_LIM = 5e3;

#define ALPHA_SIZE ('z' - 'a' + 1)
const char ALPHABET[ALPHA_SIZE + 1] = "abcdefghijklmnopqrstuvwxyz";

#define NR_DIGITS 10
const char DIGITS[NR_DIGITS + 1] = "01234546789";

char tokenToChar(const char token[MAX_CODE_LEN]) {
    if (!token) {
        return -1;
    }
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
    if (*token == '/') {
        return ' ';
    }
    return -1;
}

DynStr morseToText(const char *const morseCode) {
    const char *DELIM = " ";
    char *auxCode = ehStrdup(morseCode);
    char *token = strtok(auxCode, DELIM);
    DynStr text;
    dynStrInit(&text);
    //assert(text.size);
    while (token != NULL) {
        char ch = tokenToChar(token);
        if (ch == -1) {
            fprintf(stderr, "Invalid char!\n");
            exit(1);
        }
        dynStrAppendCh(&text, ch);
        token = strtok(NULL, DELIM);
    }
    free(auxCode);
    return text;
}

DynStr textToMorse(const char *const text) {
    DynStr ans;
    dynStrInit(&ans);
    for (int i = 0; text[i]; i++) {
        char ch = tolower(text[i]);
        if (isalpha(ch)) {
            const int pos = strchr(ALPHABET, ch) - ALPHABET;
            dynStrAppendStr(&ans, morseAlphabet[pos]);
        } else if (isdigit(ch)) {
            const int pos = ch - '0';
            dynStrAppendStr(&ans, morseDigits[pos]);
        } else if (isspace(ch)) {
            dynStrAppendStr(&ans, " / ");
        }
        else {
            fprintf(stderr, "Invalid char!\n");
            exit(1);
        }
        dynStrAppendCh(&ans, ' ');
    }
    return ans;
}

#define MILLIS_TO_SEC(millis) (1e3LL * millis)
void playMorse(const char *const morseCode) {
    for (int i = 0; morseCode[i]; i++) {
        switch (morseCode[i]) {
            case '.': 
                playDot(); 
                break;
            case '-':
                playLine();
                break;
            case ' ':
                sleep(1);
                break;
            default:
                sleep(2);
            
            sleep(1);
        }
    }
}