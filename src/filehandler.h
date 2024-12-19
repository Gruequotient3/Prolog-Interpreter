#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>

FILE* openFile(const char* path, const char* accessMode);

int getLineSize(FILE* file);

char* getLine(FILE* file);

void closeFile(FILE* file);


#endif
