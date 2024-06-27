#ifndef __FILE_H
#define __FILE_H

#include <stdio.h>
#include <stdlib.h>

FILE *openFile(const char path[], const char mode[]);
void closeFile(FILE *file);

#endif