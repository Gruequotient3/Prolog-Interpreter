#ifndef ANALYSER_C
#define ANALYSER_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errormacro.h"

#include "analyser.h"
#include "parser.h"
#include "linkedlist.h"


/*
  * Function that tell if a string is a knowledge
  * We define a knowledge by :
  *     - no Capital letter
  *     - no digits
  *     - no ":-"
*/
int isKnowledge(char* string){
    if (!string){
        NULLARGUMENT("isKnowledge");
    }

    if (parseMultipleCharInterval(string, 'A', 'Z')
        || parseMultipleCharInterval(string, '0', '9')
        || (parseChar(string, ':') && parseChar(string, '-'))
        || parseChar(string, '_'))
        return 0;
    return 1;
}


/*
 * Funtion that tell if a string is correctly structured
 * We define a good structured by :
 *      - ended by '.'
 *      - same number of '(' than ')'
 *          '(' = +1
 *          ')' = -1
 *          nbParentheses >= 0
*/
int isStructureGood(char* string){
    if (!string){
        NULLARGUMENT("isStructureGood");
    }

    int nbParentheses = 0;
    while(*string++){
        if (*string == '(')
            ++nbParentheses;
        if (*string == ')')
            --nbParentheses;

        if ((*string == '.') && (*(string+1)))
            return 0;

        if (nbParentheses < 0)
            return 0;
    }
    if (nbParentheses)
        return 0;
    return 1;

}


/*
 * Function that evaluate a knowledge expression
 * if the knowledge is write correctly then store it in linkedlist
 *      - name
 *      - parameters separated by comma
 *      - parameter not NULL
*/
llist* evalKnowledge(char* string, int line){
    if (!string){
        NULLARGUMENT("evalKnowledge");
    }

    // Get the knowledge's name
    char* name = parseCharExtractB(string, '(');
    if (!name){
        INVALIDSYNTAX(line, string);
    }

    // Get the parameters
    int nbParameters = 1;
    char* parametersString = parseCharExtractB2(string, '(', ')');
    char* str = parametersString;
    if (!parametersString){
        INVALIDSYNTAX(line, string);
    }

    // Get the number of parameters
    while (str = parseChar(str, ','))
        ++nbParameters;

    char** parameters = (char**)malloc(sizeof(char*) * nbParameters);
    for (int  i = 0; i < nbParameters; ++i){
        parameters[i] = NULL;
    }

    llist* knowledgeList = NULL;
    if (nbParameters == 1){
        if (!(*parametersString)){
            INVALIDSYNTAX(line, string);
        }
        parameters[0] = (char*)malloc(sizeof(char) * (strlen(parametersString)+1));
        strcpy(parameters[0], parametersString);
    }

    else{
        char* str = parametersString;
        char* param = NULL;
        for (int i = 0; i < nbParameters; ++i){
            param = parseCharExtractB(str, ',');
            if (!param){
                param = (char*)malloc(sizeof(char) * (strlen(str)+1));
                strcpy(param, str);
            }
            if (!(*param)){
                INVALIDSYNTAX(line, string);
            }
            str = parseChar(str, ',');
            parameters[i] = (char*)malloc(sizeof(char) * (strlen(param)+1));
            strcpy(parameters[i], param);
            free(param);
        }
    }
    knowledgeList = llNewList(name, nbParameters, llNewNode(parameters, nbParameters));

    free(name);
    free(parametersString);
    for (int i = 0; i < nbParameters; ++i){
        if (parameters[i]){
            free(parameters[i]);
        }
    }
    free(parameters);

    return knowledgeList;
}


#endif
