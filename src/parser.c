#ifndef PARSER_C
#define PARSER_C


#include <stdio.h>

#include "parser.h"

char* parseChar(char* string, char c){
    if (!string)
        return NULL;
    if (*string == c)
        return string;
    return NULL;
}

char* parseString(char* string, char* parString){
    if (!string || !parString)
        return NULL;
    if (!(*parString))
        return string;
    char* ptr = parseChar (string, *parString);
    if (!ptr)
        return NULL;
    char* par = parseString(ptr+1, parString+1);
    if (!par)
        return NULL;
    return par;
}




#endif
