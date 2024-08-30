#include "dynstr.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

const int DS_CHUNK = 2;

void dynStrInit(DynStr *ds) {
    assert(DS_CHUNK > 1);
    ds->buffer = (char*)malloc(sizeof(char));
    if (ds->buffer == NULL) {
        perror("");
        exit(1);
    }
    *ds->buffer = '\0';
    ds->cap = 1;
    ds->size = 0;
}

void dynStrGrow(DynStr *ds) {
    ds->cap += DS_CHUNK;
    ds->buffer = (char*)realloc(ds->buffer, sizeof(char) * ds->cap);
    if (ds->buffer == NULL) {
        perror("realloc");
        exit(1);
    }
    memset(ds->buffer + ds->size, 0, (ds->cap - ds->size) * sizeof(char));
}

void dynStrAppendCh(DynStr *ds, char ch) {
    if (ds->size == ds->cap - 1) {
        dynStrGrow(ds);
    }
    ds->buffer[ds->size++] = ch;
}

void dynStrAppendStr(DynStr *ds, const char *const s) {
    const int len = strlen(s);
    while (ds->size + len >= ds->cap - 1) {
        dynStrGrow(ds);
    }
    ds->size += len;
    strcat(ds->buffer, s);
}

void dynStrFree(DynStr *ds) {
    ds->cap = ds->size = 0;
    free(ds->buffer);
}

void dynStrAssign(DynStr *ds, const char *const s) {
    const int len = strlen(s);
    while (len >= ds->cap) {
        dynStrGrow(ds);
    }
    strncpy(ds->buffer, s, len);
    ds->buffer[len] = 0;
    ds->size = len;
}

void dynStrShrinkToFit(DynStr *ds) {
    ds->cap = ds->size + 1;
    ds->buffer = (char*)realloc(ds->buffer, sizeof(char) * (ds->size + 1));
}