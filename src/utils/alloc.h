#ifndef __ALLOC_H
#define __ALLOC_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void* ehMalloc(size_t size);
void* ehCalloc(size_t nmemb, size_t size);
void** allocMatrix(size_t lines, size_t cols, size_t size);
void freeMatrix(void **matrix, size_t lines);

#endif