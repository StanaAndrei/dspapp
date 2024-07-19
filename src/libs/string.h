#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <string.h>

#define STRSIZE 10

typedef struct {
    char *str;
    unsigned int size;
} string;

string *str_create(char *init);
void str_free(string *s);

void str_grow(string *s);
void str_growto(string *s, unsigned int newsize);
void str_shrink(string *s);

unsigned int str_sizeof(string *s);
unsigned int str_length(string *s);

void str_append(string *s, char *app);
void str_cappend(string *s, char c);

char str_getc(string *s, unsigned int index);
char *str_get(string *s);

void str_set(string *s, char *newstr);

#endif