#include "file.h"

FILE *openFile(const char path[], const char mode[]) {
    FILE *file = fopen(path, mode);
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }
    return file;
}

void closeFile(FILE *file) {
    if (fclose(file) == -1) {
        perror("fclose");
    }
}