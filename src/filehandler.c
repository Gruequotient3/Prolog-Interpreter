#ifndef FILE_HANDLER_C
#define FILE_HANDLER_C

#include <stdlib.h>

#include "filehandler.h"

FILE* openFile(const char* path, const char* accessMode){
    FILE* file = fopen(path, accessMode);
    if (!file){
        printf("Error : Failed to load file at path %s in openFile\n", path);
        exit(1);
    }
    return file;
}

int getLineSize(FILE* file){
    int str;
    int pos = ftell(file);
    while ((str = fgetc(file)) != EOF && str != '\n');
    int endPos = ftell(file);
    fseek(file, pos, SEEK_SET);
    return endPos - pos;
}

char* getLine(FILE* file){
    int lineSize = getLineSize(file);
    char* str = (char*) malloc(lineSize);
    fgets(str, lineSize, file);
    return str;
}

void closeFile(FILE* file){
    fclose(file);
}


#endif
