#ifndef LINKED_LIST_C
#define LINKED_LIST_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"


/*
 * Function that create a new linkedlist
*/
llist* llNewList(char* name, int arity, llnode* node){
    llist* list = (llist*)malloc(sizeof(llist));
    if (!list){
        printf("Error : Failed to initialize list in llNewList\n");
        exit(1);
    }
    list->name = (char*)malloc(sizeof(char) * (strlen(name)+1));
    if (!list->name){
        printf("Error : Failed to initialize list name in llNewList\n");
        exit(1);
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
llnode* llNewNode(char** data, int size){
    llnode* node = (llnode*)malloc(sizeof(llnode));
    if (!node){
        printf("Error : Failed to initialize node in llNewNode\n");
        exit(1);
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
void llInsert(llist* list, llnode** pos, llnode* node){
    if (!list || !node){
        printf("Error : Wrong argument (NULL llist or llnode) in llInsert\n");
        exit(1);
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
void llPushFront(llist* list, llnode* node){
    llInsert(list, &list->first, node);
}

/*
 * Function that insert a new node at the end of the linked list
*/
void llPushBack(llist* list, llnode* node){
    llInsert(list, NULL, node);
}


/*
 * Function that remove the node at the start of the linked list
*/
char** llPopFront(llist* list){
    if (!list || !list->first){
        printf("Error : Wrong argument can't extract empty list in llPopFront\n");
        exit(1);
    }
    char** n;
    llnode* first = list->first;
    n = (char**)malloc(sizeof(char*) * first->size);
    for (int i = 0; i < first->size; ++i){
        n[i] = (char*)malloc(sizeof(char) * (strlen(first->data[i])+1));
        strcpy(n[i], first->data[i]);
    }
    list->first = first->next;
    first->next = NULL;
    llClearNode(first);
    return n;
}

/*
 * Function that remove the node at the end of the linked list
*/
char** llPopBack(llist* list){
    if (!list || !list->first){
        printf("Error : Wrong argument can't extract empty list in llPopBack\n");
        exit(1);
    }
    char** n;
    llnode* node = list->first;
    if (list->first == list->last){
        n = (char**)malloc(sizeof(char*) * node->size);
        for (int i = 0; i < node->size; ++i){
            n[i] = (char*)malloc(sizeof(char) * (strlen(node->data[i])+1));
            strcpy(n[i], node->data[i]);
        }
        list->first = NULL;
        list->last = NULL;
        llClearNode(node);
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
    llClearNode(list->last);
    list->last = node;
    return n;
}

/*
 * Function that print all the value of each node in the linked list
*/
void llPrint(llist* list){
    if (!list)
        return;
    llnode* node = list->first;
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
void llClearNode(llnode* node){
    if (!node)
        return;
    llClearNode(node->next);
    for (int i = 0; i < node->size; ++i){
        free(node->data[i]);
    }
    free(node->data);
    free(node);
}


/*
 * Function that free the linked list
*/
void llClearList(llist** list){
    if (!list){
        printf("Error : Wrong argument (NULL llist) in llClearList\n");
        exit(1);
    }
    llClearNode((*list)->first);
    free((*list)->name);
    free(*list);
    *list = NULL;
}






#endif
