#ifndef KNOWLEDGE_TREE_C
#define KNOWLEDGE_TREE_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knowledgetree.h"
#include "errormacro.h"



/*
 * Function that create a new tree
*/
ktnode* ktNewTree(ktelement* data, ktnode* lchild, ktnode* rchild){
    if (!data){
        NULLARGUMENT("ktNewNode");
    }

    ktnode* node = (ktnode*)malloc(sizeof(ktnode));
    if (!node){
        FAILEDALLOCATEMEMORY("ktNewNode");
    }
    node->data = data;
    node->lchild = lchild;
    node->rchild = rchild;
    return node;
}

/*
 * Function that create a new tree with NULL children
*/
ktnode* ktNewNode(ktelement* data){
    return ktNewTree(data, NULL, NULL);
}

void ktInsertNode(ktnode** pos, ktnode* newNode){
    if (!newNode){
        NULLARGUMENT("ktInsertNode");
    }
    ktnode* previous = *pos;
    *pos = newNode;
    if (previous != NULL){
        if (previous->data->arity < newNode->data->arity){
            newNode->lchild = previous;
        }
        else{
            newNode->rchild = previous;
        }
    }
}

/*
 * Function that insert a node inside a tree
 * Nodes are insert by BST insert
*/
void ktInsert(ktnode** t, ktelement* data){
    if (!t && !data){
        NULLARGUMENT("ktInsert");
    }
    ktnode** pos = ktFindOrderedPosition(t, data);
    ktInsertNode(pos, ktNewNode(data));

}

/*
 * Function that find the node where to insert data
*/
ktnode** ktFindOrderedPosition(ktnode** t, ktelement* data){
    if(!t){
        NULLARGUMENT("ktFindOrderedPosition");
    }
    if (!*t){
        return t;
    }
    if (data->arity < (*t)->data->arity)
        return ktFindOrderedPosition(&(*t)->lchild, data);
    return ktFindOrderedPosition(&(*t)->rchild, data);
}

/*
 * Function that find the data in the tree equal to name and arity
*/
ktelement* ktFind(ktnode* tree, char* name, int arity){
    if (!tree)
        return NULL;
    if (tree->data->arity == arity && !strcmp(tree->data->name, name))
        return tree->data;
    if (tree->data->arity > arity)
        return ktFind(tree->lchild, name, arity);
    return ktFind(tree->rchild, name, arity);
}

/*
 * Function that print the tree in postfix order
*/
void ktPostfixPrint(ktnode* t){
    if (!t)
        return;
    ktPostfixPrint(t->lchild);
    ktPostfixPrint(t->rchild);
    klPrint(t->data);
}

/*
 * Function that free the tree from memory
*/
void ktClearTree(ktnode** t){
    if (!t){
        NULLARGUMENT("ktClearTree");
    }
    if (!*t)
        return;
    ktClearTree(&(*t)->lchild);
    ktClearTree(&(*t)->rchild);
    klClearList(&(*t)->data);
    free(*t);
    *t = NULL;
}



#endif
