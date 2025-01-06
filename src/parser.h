#ifndef PARSER_H
#define PARSER_H


char* parseEOS (char* string, char c);
char* parseStartChar(char* string, char c);
char* parseChar(char* string, char c);
char* parseMultipleCharInterval(char* string, char c1, char c2);
char* parseCharExtractB(char* string, char c);
char* parseCharExtractA(char* string, char c);
char* parseCharExtractB2(char* string, char c1, char c2);

char* parseStartString(char* string, char* parString);
#endif
