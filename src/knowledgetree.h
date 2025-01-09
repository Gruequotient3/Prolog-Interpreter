#ifndef KNOWLEDGE_TREE_H
#define KNOWLEDGE_TREE_H

#include "knowledgelist.h"

typedef klist ktelement;
typedef struct ktnode_t ktnode;

struct ktnode_t{
    ktelement* data;
    struct ktnode_t* lchild;
    struct ktnode_t* rchild;
};

ktnode* ktNewTree(ktelement* data, ktnode* lchild, ktnode* rchild);
ktnode* ktNewNode(ktelement* data);

void ktInsertNode(ktnode** pos, ktnode* newNode);
void ktInsert(ktnode** t, ktelement* data);

ktnode** ktFindOrderedPosition(ktnode** t, ktelement* data);

ktelement* ktFind(ktnode* tree, char* name, int arity);

void ktPostfixPrint(ktnode* t);

void ktClearTree(ktnode** t);


#endif
