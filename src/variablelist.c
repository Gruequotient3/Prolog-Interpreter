#ifndef VARIABLE_LIST_C
#define VARIABLE_LIST_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variablelist.h"
#include "errormacro.h"


/*
 * Function that create a new linkedlist
*/
vlist* vlNewList(vlnode* node){
    vlist* list = (vlist*)malloc(sizeof(vlist));
    if (!list){
        FAILEDALLOCATEMEMORY("vlNewList");
    }
    list->first = node;
    list->last = node;
    return list;
}

/*
 * Function that create a new node
*/
vlnode* vlNewNode(char* name, char* data){
    vlnode* node = (vlnode*)malloc(sizeof(vlnode));
    if (!node){
        FAILEDALLOCATEMEMORY("klNewNode");
    }
    node->name = (char*)malloc(sizeof(char) * (strlen(name)+1));
    strcpy(node->name, name);
    node->data = (char*)malloc(sizeof(char) * (strlen(data)+1));
    strcpy(node->data, data);
    node->next  = NULL;
    return node;
}

/*
 * Function that insert a node in a linked list at a specific pos
*/
void vlInsert(vlist* list, vlnode** pos, vlnode* node){
    if (!list || !node){
        NULLARGUMENT("vlInsert");
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

void vlModify(vlnode** pos, char* newData){
    if (!pos){
        NULLARGUMENT("vlModify");
    }
    if (!*pos)
        return;
    free((*pos)->data);
    (*pos)->data = (char*)malloc(sizeof(char) * (strlen(newData)+1));
    strcpy((*pos)->data, newData);
}

/*
 * Function that insert a new node at the start of the linked list
*/
void vlPushFront(vlist* list, vlnode* node){
    vlInsert(list, &list->first, node);
}

/*
 * Function that insert a new node at the end of the linked list
*/
void vlPushBack(vlist* list, vlnode* node){
    vlInsert(list, NULL, node);
}


/*
 * Function that remove the node at the start of the linked list
*/
char* vlPopFront(vlist* list){
    if (!list || !list->first){
        NULLARGUMENT("vlPopFront");
    }
    char* n;
    vlnode* first = list->first;
    n = (char*)malloc(sizeof(char) * (strlen(first->data)+1));
    strcpy(n, first->data);
    list->first = first->next;
    first->next = NULL;
    vlClearNode(first);
    return n;
}

/*
 * Function that remove the node at the end of the linked list
*/
char* vlPopBack(vlist* list){
    if (!list || !list->first){
        NULLARGUMENT("vlPopBack");
    }
    char* n;
    vlnode* node = list->first;
    if (list->first == list->last){
        n = (char*)malloc(sizeof(char) * (strlen(node->data)+1));
        strcpy(n, node->data);
        list->first = NULL;
        list->last = NULL;
        vlClearNode(node);
        return n;
    }
    while (node->next != list->last && node){
        node = node->next;
    }
    node->next = NULL;
    n = (char*)malloc(sizeof(char) * (strlen(list->last->data)+1));
    strcpy(n, list->last->data);
    vlClearNode(list->last);
    list->last = node;
    return n;
}

/*
 * Function that say if a value is already stored in the linked list
 * return :
 *      0 : false
 *      1 : true
*/
int vlExist(vlist* list, char* name){
    if (!list){
        return 0;
    }
    vlnode* node = list->first;
    while(node){
        if (!strcmp(name, node->name)){
            return 1;
        }
        node = node->next;
    }
    return 0;
}

vlnode* vlFind(vlist* list, char* name){
    if (!list){
        return NULL;
    }
    vlnode* node = list->first;
    while (node){
        if (!strcmp(node->name, name))
            return node;
        node = node->next;
    }
    return NULL;

}


/*
 * Function that print all the value of each node in the linked list
*/
void vlPrint(vlist* list){
    if (!list)
        return;
    vlnode* node = list->first;
    while (node){
        printf("%s -> %s\n", node->name, node->data);
        node = node->next;
    }

}

/*
 * Function that free all the node after this node (including the current node)
*/
void vlClearNode(vlnode* node){
    if (!node)
        return;
    vlClearNode(node->next);
    free(node->name);
    free(node->data);
    free(node);
}


/*
 * Function that free the linked list
*/
void vlClearList(vlist** list){
    if (!list){
        NULLARGUMENT("vlClearList");
    }
    if (!*list)
        return;
    vlClearNode((*list)->first);
    free(*list);
    *list = NULL;
}






#endif
