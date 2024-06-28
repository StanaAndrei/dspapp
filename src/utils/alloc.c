#include "alloc.h"

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