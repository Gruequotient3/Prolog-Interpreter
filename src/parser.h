#ifndef PARSER_H
#define PARSER_H


char* parseStartChar(char* string, char c);
char* parseChar(char* string, char c);
char* parseCharExtractB(char* string, char c);
char* parseCharExtractA(char* string, char c);
char* parseCharExtractB2(char* string, char c1, char c2);

char* parseStartString(char* string, char* parString);
#endif
