#ifndef KNOWLEDGE_LIST_C
#define KNOWLEDGE_LIST_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knowledgelist.h"
#include "errormacro.h"


/*
 * Function that create a new linkedlist
*/
klist* klNewList(char* name, int arity, klnode* node){
    klist* list = (klist*)malloc(sizeof(klist));
    if (!list){
        FAILEDALLOCATEMEMORY("klNewList");
    }
    list->name = (char*)malloc(sizeof(char) * (strlen(name)+1));
    if (!list->name){
        FAILEDALLOCATEMEMORY("klNewList");
    }
    strcpy(list->name, name);
    list->arity = arity;
    list->first = node;
    list->last = node;
    return list;
}

/*
 * Function that create a new node
*/
klnode* klNewNode(char** data, int size){
    klnode* node = (klnode*)malloc(sizeof(klnode));
    if (!node){
        FAILEDALLOCATEMEMORY("klNewNode");
    }

    node->data = (char**)malloc(sizeof(char*) * size);
    for (int i = 0; i < size; ++i){
        node->data[i] = (char*)malloc(sizeof(char) * (strlen(data[i])+1));
        strcpy(node->data[i], data[i]);
    }
    node->size = size;
    node->next  = NULL;
    return node;
}

/*
 * Function that insert a node in a linked list at a specific pos
*/
void klInsert(klist* list, klnode** pos, klnode* node){
    if (!list || !node){
        NULLARGUMENT("klInsert");
    }

    /*
    * Insert at the end of the list
    * When pos == NULL
    */
    if (!pos){
        (list->last)->next = node;
        list->last = node;
        return;
    }

    node->next = *pos;
    *pos = node;
}

/*
 * Function that insert a new node at the start of the linked list
*/
void klPushFront(klist* list, klnode* node){
    klInsert(list, &list->first, node);
}

/*
 * Function that insert a new node at the end of the linked list
*/
void klPushBack(klist* list, klnode* node){
    klInsert(list, NULL, node);
}


/*
 * Function that remove the node at the start of the linked list
*/
char** klPopFront(klist* list){
    if (!list || !list->first){
        NULLARGUMENT("klPopFront");
    }
    char** n;
    klnode* first = list->first;
    n = (char**)malloc(sizeof(char*) * first->size);
    for (int i = 0; i < first->size; ++i){
        n[i] = (char*)malloc(sizeof(char) * (strlen(first->data[i])+1));
        strcpy(n[i], first->data[i]);
    }
    list->first = first->next;
    first->next = NULL;
    klClearNode(first);
    return n;
}

/*
 * Function that remove the node at the end of the linked list
*/
char** klPopBack(klist* list){
    if (!list || !list->first){
        NULLARGUMENT("klPopBack");
    }
    char** n;
    klnode* node = list->first;
    if (list->first == list->last){
        n = (char**)malloc(sizeof(char*) * node->size);
        for (int i = 0; i < node->size; ++i){
            n[i] = (char*)malloc(sizeof(char) * (strlen(node->data[i])+1));
            strcpy(n[i], node->data[i]);
        }
        list->first = NULL;
        list->last = NULL;
        klClearNode(node);
        return n;
    }
    while (node->next != list->last && node){
        node = node->next;
    }
    node->next = NULL;
    n = (char**)malloc(sizeof(char*) * list->last->size);
    for (int i = 0; i < list->last->size; ++i){
        n[i] = (char*)malloc(sizeof(char) * (strlen(list->last->data[i])+1));
        strcpy(n[i], list->last->data[i]);
    }
    klClearNode(list->last);
    list->last = node;
    return n;
}

/*
 * Function that say if a value is already stored in the linked list
 * return :
 *      0 : false
 *      1 : true
*/
int klExist(klist* list, char** data, int size){
    if (!list){
        return 0;
    }
    klnode* node = list->first;
    int find = 0;
    while(node && !find){
        find = 1;
        for (int i = 0; i < node->size && i < size; ++i){
            if (strcmp(data[i], node->data[i])){
                find = 0;
                break;
            }
        }
        node = node->next;
    }
    return find;
}

/*
 * Function that print all the value of each node in the linked list
*/
void klPrint(klist* list){
    if (!list)
        return;
    klnode* node = list->first;
    printf("name : %s\n", list->name);
    printf("arity : %d\n", list->arity);
    while (node){
        printf("(");
        for (int i = 0; i < node->size; ++i){
            if (i == node->size-1)
                printf("%s", node->data[i]);
            else{
                printf("%s, ", node->data[i]);
            }
        }
        printf(")\n");
        node = node->next;
    }
    printf("NULL\n");

}

/*
 * Function that free all the node after this node (including the current node)
*/
void klClearNode(klnode* node){
    if (!node)
        return;
    klClearNode(node->next);
    for (int i = 0; i < node->size; ++i){
        free(node->data[i]);
    }
    free(node->data);
    free(node);
}


/*
 * Function that free the linked list
*/
void klClearList(klist** list){
    if (!list){
        NULLARGUMENT("klClearList");
    }
    klClearNode((*list)->first);
    free((*list)->name);
    free(*list);
    *list = NULL;
}






#endif
