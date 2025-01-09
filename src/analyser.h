#ifndef ANALYSER_H
#define ANALYSER_H

#include "linkedlist.h"
#include "binarytree.h"

int isKnowledge(char* string);
int isStructureGood(char* string);

void evalKnowledge(btnode** tree, char* string, int line);
int evalQuestion(btnode** tree, char* string);



#endif
