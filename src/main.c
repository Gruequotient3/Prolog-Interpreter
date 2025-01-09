#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "filehandler.h"
#include "analyser.h"
#include "knowledgelist.h"
#include "knowledgetree.h"
#include "variablelist.h"


void storeFileContent(FILE* file, ktnode** knowledgeTree);
void evaluateInput(ktnode** knowledgeTree);

int main(int argc, char* argv[]){
    FILE* file = NULL;
    if (argc != 2){
        printf("Need Correct argument : ./main <path prolog file>\n");
        return 0;
    }
    else{
        file = openFile(argv[1], "r+");
    }

    ktnode* knowledgeTree = NULL;
    storeFileContent(file, &knowledgeTree);

    printf("--- Knowldege extract from file ---\n \n");
    ktPostfixPrint(knowledgeTree);

    evaluateInput(&knowledgeTree);

    closeFile(file);
    ktClearTree(&knowledgeTree);
    return 0;

}

void storeFileContent(FILE* file, ktnode** knowledgeTree){
    char* str = NULL;
    int line = 0;
    int out = 0;
    do{
        str = getLine(file);
        if (isStructureGood(str) && isKnowledge(str)){
            evalKnowledge(knowledgeTree, str, line);
        }
        if (!*str){
            out = 1;
        }
        free(str);
    }while(!out);
}


void evaluateInput(ktnode** knowledgeTree){

    vlist* variables = NULL;
    vlist* result = NULL;
    while(1){

        char question[128];
        printf("Quit (type : quit)\n");
        printf("?- ");
        fflush(stdin);
        fgets(question, 128, stdin);
        if (parseStartString(question, "quit"))
            break;
        printf("%s\n\n", evalQuestion(knowledgeTree,
                     &variables, question, &result) ? "true" : "false");
        vlPrint(result);
        vlClearList(&variables);
        vlClearList(&result);
        variables = NULL;
        result = NULL;
    }



}
