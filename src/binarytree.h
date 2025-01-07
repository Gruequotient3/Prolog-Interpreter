#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "linkedlist.h"

typedef llist btelement;
typedef struct btnode_t btnode;

struct btnode_t{
    btelement* data;
    struct btnode_t* lchild;
    struct btnode_t* rchild;
};

btnode* btNewTree(btelement* data, btnode* lchild, btnode* rchild);
btnode* btNewNode(btelement* data);

void btInsertNode(btnode** pos, btnode* newNode);
void btInsert(btnode** t, btelement* data);

btnode** btFindOrderedPosition(btnode** t, btelement* data);

btelement* btFind(btnode* tree, char* name, int arity);

void btPostfixPrint(btnode* t);


void btClearTree(btnode** t);


#endif
