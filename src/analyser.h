#ifndef ANALYSER_H
#define ANALYSER_H

#include "knowledgelist.h"
#include "knowledgetree.h"
#include "variablelist.h"

int isKnowledge(char* string);
int isStructureGood(char* string);

void evalKnowledge(ktnode** tree, char* string, int line);
int evalQuestion(ktnode** tree, char* string);



#endif
