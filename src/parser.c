#ifndef PARSER_C
#define PARSER_C


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "parser.h"

/*
 * Parsing that get the adress of the NULL character in a string
*/
char* parseEOS (char* string, char c){
    if (!string){
        printf("Error : Wrong argument (NULL string) in parseEOS\n");
        exit(1);
    }

    while (*string)
        ++string;
    return string;
}

/*
 * Parsing that get the address of a character in a string
 * The character need to be at the start of the string
*/
char* parseStartChar(char* string, char c){
    if (!string){
        printf("Error : Wrong argument (NULL string) in parseStartChar\n");
        exit(1);
    }

    if (*string == c)
        return string;
    return NULL;
}

/*
 * Parsing that get the adress of a string after a character in a string
*/
char* parseChar(char* string, char c){
    if (!string){
        printf("Error : Wrong argument (NULL string) in parseChar\n");
        exit(1);
    }

    if (!(*string))
        return NULL;

    char* ptr = parseStartChar (string, c);
    if (ptr)
        return ptr + 1;
    char* par = parseChar(string + 1, c);
    return par;
}

/*
 * Parsing that get the adress of after the character find between 2 ASCII value
*/
char* parseMultipleCharInterval(char* string, char c1, char c2){
    if (!string){
        printf("Error : Wrong argument (NULL string) in parseMultipleChar\n");
        exit(1);
    }
    char* str = NULL;
    while (!str && c1 <= c2){
        str = parseChar(string, c1);
        ++c1;
    }
    return str;
}

/*
 * Parsing that extract a string before the character in a string
*/
char* parseCharExtractB(char* string, char c){
    if (!string){
        printf("Error : Wrong argument (NULL string) in parseCharExtractB\n");
        exit(1);
    }

    char* par = parseChar(string, c);
    if (!par)
        return NULL;
    par--;
    unsigned short nbChar = par - string;
    char* extract = (char*)malloc(sizeof(char) * nbChar + 1);
    if (!extract){
        printf("Error : Failed to allocate memory in parseCharExtractB\n");
        exit(1);
    }
    for (int i = 0; i < nbChar; ++i){
        extract[i] = string[i];
    }
    extract[nbChar] = 0;
    return extract;
}

/*
 * Parsing that extract a string after the character in a string
*/
char* parseCharExtractA(char* string, char c){
    if (!string){
        printf("Error : Wrong argument (NULL string) in parseCharExtractA\n");
        exit(1);
    }

    char* par = parseChar(string, c);
    if (!par)
        return NULL;
    char* eos = parseEOS(par, c);
    unsigned short nbChar = eos - par;
    char* extract = (char*) malloc(sizeof(char) * nbChar+1);
    if (!extract){
        printf("Error : Failed to allocate memory in parseCharExtractA\n");
        exit(1);
    }
    for (int i = 0; i < nbChar; ++i){
        extract[i] = par[i];
    }
    extract[nbChar] = 0;
    return extract;

}

/*
 * Parsing that extract a string between 2 characters in string
*/
char* parseCharExtractB2(char* string, char c1, char c2){
    if (!string){
        printf("Error : Wrong argument (NULL string) in parseCharExtractB2\n");
        exit(1);
    }

    char* par1 = parseChar(string, c1);
    if (!par1) return NULL;
    char* par2 = parseChar(par1, c2);
    if (!par2)
        return NULL;
    --par2;
    short nbChar = par2 - par1;
    char* extract = (char*)malloc(sizeof(char) * nbChar + 1);
    if (!extract){
        printf("Error : Failed to allocate memory in parseCharExtractB2\n");
        exit(1);
    }
    for (int i = 0; i < nbChar; ++i){
        extract[i] = par1[i];
    }
    extract[nbChar] = 0;
    return extract;

}

/*
* Parsing that get the adress of the end of the pattern in a string
* The pattern need to be at the start of the string to be found
*/
char* parseStartString(char* string, char* parString){
    if (!string || !parString){
        printf("Error : Wrong argument (NULL string) in parseStartString\n");
        exit(1);
    }

    if (!(*parString))
        return string;
    char* ptr = parseStartChar (string, *parString);
    if (!ptr)
        return NULL;
    char* par = parseStartString(ptr + 1, parString + 1);
    if (!par)
        return NULL;
    return par;
}



#endif
