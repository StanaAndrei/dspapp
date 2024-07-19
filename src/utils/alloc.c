#include "alloc.h"

#include <string.h>

void* ehMalloc(size_t size) {
    void *mem = malloc(size);
    if (mem == NULL) {
        perror("malloc");
        exit(1);
    }
    return mem;
}

void* ehCalloc(size_t nmemb, size_t size) {
    void *mem = calloc(nmemb, size);
    if (mem == NULL) {
        perror("calloc");
        exit(1);
    }
    return mem;
}

void** allocMatrix(size_t lines, size_t cols, size_t size) {
    void **matrix = ehCalloc(lines, sizeof(void*));
    for (size_t i = 0; i < lines; i++) {
        matrix[i] = ehCalloc(cols, size);
    }
    return matrix;
}

void freeMatrix(void **matrix, size_t lines) {
    for (size_t i = 0; i < lines; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

char* ehStrdup(const char *const buffer) {
    char *duplicated = strdup(buffer);
    if (duplicated == NULL) {
        perror("strdup");
        exit(1);
    }
    return duplicated;
}