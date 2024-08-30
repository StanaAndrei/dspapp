#ifndef __DYNSTR_H
#define __DYNSTR_H

typedef struct {
    char *buffer;
    int cap, size;
} DynStr;

extern const int DS_CHUNK;

void dynStrInit(DynStr *ds);
void dynStrAppendCh(DynStr *ds, char ch);
void dynStrAppendStr(DynStr *ds, const char *const s);
void dynStrFree(DynStr *ds);
void dynStrAssign(DynStr *ds, const char *const s);
void dynStrShrinkToFit(DynStr *ds);

#endif