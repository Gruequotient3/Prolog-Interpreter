#ifndef ANALYSER_C
#define ANALYSER_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errormacro.h"

#include "analyser.h"
#include "parser.h"

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
    if (!*string)
        return 0;
    while(*string++){
        if (*string == '(')
            ++nbParentheses;
        if (*string == ')')
            --nbParentheses;

        if ((*string == '.') && (*(string+1)) && (*(string+1)) != '\n')
            return 0;

        if (nbParentheses < 0)
            return 0;
    }
    if (nbParentheses)
        return 0;
    return 1;

}


int isVariable(char* string){
    if (!string){
        NULLARGUMENT("isVariable");
    }
    return (*string >= 65 && *string <= 90);
}

/*
 * Function that evaluate a knowledge expression
 * if the knowledge is write correctly then store it in linkedlist
 *      - name
 *      - parameters separated by comma
 *      - parameter not NULL
*/
void evalKnowledge(ktnode** tree, char* string, int line){
    if (!string || !tree){
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

    ktelement* knowledgeList = NULL;
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

    knowledgeList = ktFind(*tree, name, nbParameters);
    if (!knowledgeList){
        ktInsert(tree, klNewList(name, nbParameters, klNewNode(parameters, nbParameters)));
    }
    else{
        if (!klExist(knowledgeList, parameters, nbParameters))
            klPushBack(knowledgeList, klNewNode(parameters, nbParameters));
    }
    free(name);
    free(parametersString);
    for (int i = 0; i < nbParameters; ++i){
        if (parameters[i]){
            free(parameters[i]);
        }
    }
    free(parameters);
}

int evalQuestion(ktnode** tree, vlist** variables, char* string, vlist** result){
    if (!string || !tree || !variables || !result){
        NULLARGUMENT("evalQuestion");
    }

    // Get requested knowledge name
    char* name = parseCharExtractB(string, '(');
    if (!name){
        INVALIDSYNTAXQ(string);
    }

    int nbParameters = 1;
    // Get the parameters
    char* parametersString = parseCharExtractB2(string, '(', ')');
    char* str = parametersString;
    if (!parametersString){
        INVALIDSYNTAXQ(string);
    }

    // Get the number of parameters
    while (str = parseChar(str, ','))
        ++nbParameters;

    char** parameters = (char**)malloc(sizeof(char*) * nbParameters);
    for (int  i = 0; i < nbParameters; ++i){
        parameters[i] = NULL;
    }

    ktelement* knowledgeList = NULL;
    if (nbParameters == 1){
        if (!(*parametersString)){
            INVALIDSYNTAXQ(string);
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
                INVALIDSYNTAXQ(string);
            }
            str = parseChar(str, ',');
            parameters[i] = (char*)malloc(sizeof(char) * (strlen(param)+1));
            strcpy(parameters[i], param);
            free(param);
        }
    }

    // Count and create each variables in the question
    for (int i = 0; i < nbParameters; ++i){
        if (isVariable(parameters[i])){
            if (!*variables){
                *variables = vlNewList(vlNewNode(parameters[i], ""));
            }
            else{
                if (!vlExist(*variables, parameters[i]));
                vlPushBack(*variables, vlNewNode(parameters[i], ""));
            }
        }
    }

    // Search in knowledge if it exist
    int question = 0;
    ktelement* node = ktFind(*tree, name, nbParameters);
    if (node){
        klnode* data = node->first;
        if (!*variables){
            while (data && !question){
                question = 1;
                for (int i = 0; i < data->size; ++i){
                    if (strcmp(parameters[i], data->data[i])){
                        question = 0;
                        break;
                    }
                }
                data = data->next;
            }
        }
        // If there is at least 1 variable
        else{
            while (data){
                question = 1;
                // Search trough all parameters
                for (int i = 0; i < data->size; ++i){
                    // If the parameter is a variable so we change it value
                    // And continue to loop through other parameter
                    if (isVariable(parameters[i])){
                        vlnode* variable = vlFind(*variables, parameters[i]);
                        vlModify(&variable, data->data[i]);
                        continue;
                    }
                    if (strcmp(parameters[i], data->data[i])){
                        question = 0;
                        break;
                    }
                }
                if (question){
                    for (int i = 0; i < data->size; ++i){
                        if (isVariable(parameters[i])){
                            vlnode* variable = vlFind(*variables, parameters[i]);
                            if (!*result){
                                *result = vlNewList(vlNewNode(parameters[i], variable->data));
                                continue;
                            }
                            vlPushBack(*result, vlNewNode(parameters[i], variable->data));
                        }
                    }
                }
                data = data->next;
            }
        }
    }
    // Else it's a rule or didn't exist

    free(name);
    free(parametersString);
    for (int i = 0; i < nbParameters; ++i){
        if (parameters[i]){
            free(parameters[i]);
        }
    }
    free(parameters);
    return question;
}


#endif
