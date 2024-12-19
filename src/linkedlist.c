#ifndef LINKED_LIST_C
#define LINKED_LIST_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"



llist* llNewList(llnode* node){
    llist* list = (llist*)malloc(sizeof(llist));
    if (!list){
        printf("Error : Failed to initialize list in llNewList\n");
        exit(1);
    }
    list->first = node;
    list->last = node;
    return list;
}

llnode* llNewNode(char* data){
    llnode* node = (llnode*)malloc(sizeof(llnode));
    if (!node){
        printf("Error : Failed to initialize node in llNewNode\n");
        exit(1);
    }
    node->data = (char*)malloc(strlen(data)+1);
    strcpy(node->data, data);
    node->next  = NULL;
    return node;
}

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

void llPushFront(llist* list, llnode* node){
    llInsert(list, &list->first, node);
}

void llPushBack(llist* list, llnode* node){
    llInsert(list, NULL, node);
}


char* llPopFront(llist* list){
    if (!list || !list->first){
        printf("Error : Wrong argument can't extract empty list in llPopFront\n");
        exit(1);
    }
    char* n;
    llnode* first = list->first;
    n = (char*)malloc(strlen(first->data)+1);
    strcpy(n, first->data);
    list->first = first->next;
    first->next = NULL;
    llClearNode(first);
    return n;
}

char* llPopBack(llist* list){
    if (!list || !list->first){
        printf("Error : Wrong argument can't extract empty list in llPopBack\n");
        exit(1);
    }
    char* n;
    llnode* node = list->first;
    if (list->first == list->last){
        n = node->data;
        list->first = NULL;
        list->last = NULL;
        llClearNode(node);
        return n;
    }
    while (node->next != list->last && node){
        node = node->next;
    }
    node->next = NULL;
    n = (char*)malloc(strlen(list->last->data)+1);
    strcpy(n, list->last->data);
    llClearNode(list->last);
    list->last = node;
    return n;
}

void llPrint(llist* list){
    if (!list)
        return;
    llnode* node = list->first;
    while (node){
        printf("%s -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");

}


void llClearNode(llnode* node){
    if (!node)
        return;
    llClearNode(node->next);
    free(node->data);
    free(node);
}


void llClearList(llist** list){
    if (!list){
        printf("Error : Wrong argument (NULL llist) in llClearList\n");
        exit(1);
    }
    llClearNode((*list)->first);
    free(*list);
    *list = NULL;
}






#endif
