#ifndef FILE_HANDLER_C
#define FILE_HANDLER_C

#include <stdlib.h>

#include "filehandler.h"


/*
 * Function that open file and return FILE's pointer
*/
FILE* openFile(const char* path, const char* accessMode){
    FILE* file = fopen(path, accessMode);
    if (!file){
        printf("Error : Failed to load file at path %s in openFile\n", path);
        exit(1);
    }
    return file;
}

/*
 * Function that return the lenght of the line
*/
int getLineSize(FILE* file){
    int str;
    int pos = ftell(file);
    while ((str = fgetc(file)) != EOF && str != '\n');
    int endPos = ftell(file) + 1;
    fseek(file, pos, SEEK_SET);
    return endPos - pos;
}

/*
 * Function that return a whole line
*/
char* getLine(FILE* file){
    int lineSize = getLineSize(file);
    char* str = (char*) malloc(lineSize);
    fgets(str, lineSize, file);
    return str;
}

/*
 * Function that close a file
*/
void closeFile(FILE* file){
    fclose(file);
}


#endif
