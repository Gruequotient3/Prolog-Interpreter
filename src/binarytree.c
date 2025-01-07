#ifndef BINARY_TREE_C
#define BINARY_TREE_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binarytree.h"
#include "errormacro.h"



/*
 * Function that create a new tree
*/
btnode* btNewTree(btelement* data, btnode* lchild, btnode* rchild){
    if (!data){
        NULLARGUMENT("btNewNode");
    }

    btnode* node = (btnode*)malloc(sizeof(btnode));
    if (!node){
        FAILEDALLOCATEMEMORY("btNewNode");
    }
    node->data = data;
    node->lchild = lchild;
    node->rchild = rchild;
    return node;
}

/*
 * Function that create a new tree with NULL children
*/
btnode* btNewNode(btelement* data){
    return btNewTree(data, NULL, NULL);
}

void btInsertNode(btnode** pos, btnode* newNode){
    if (!newNode){
        NULLARGUMENT("btInsertNode");
    }
    btnode* previous = *pos;
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
void btInsert(btnode** t, btelement* data){
    if (!t && !data){
        NULLARGUMENT("btInsert");
    }
    btnode** pos = btFindOrderedPosition(t, data);
    btInsertNode(pos, btNewNode(data));

}

/*
 * Function that find the node where to insert data
*/
btnode** btFindOrderedPosition(btnode** t, btelement* data){
    if(!t){
        NULLARGUMENT("btFindOrderedPosition");
    }
    if (!*t){
        return t;
    }
    if (data->arity < (*t)->data->arity)
        return btFindOrderedPosition(&(*t)->lchild, data);
    return btFindOrderedPosition(&(*t)->rchild, data);
}

/*
 * Function that find the data in the tree equal to name and arity
*/
btelement* btFind(btnode* tree, char* name, int arity){
    if (!tree)
        return NULL;
    if (tree->data->arity == arity && !strcmp(tree->data->name, name))
        return tree->data;
    if (tree->data->arity > arity)
        return btFind(tree->lchild, name, arity);
    return btFind(tree->rchild, name, arity);
}

/*
 * Function that print the tree in postfix order
*/
void btPostfixPrint(btnode* t){
    if (!t)
        return;
    btPostfixPrint(t->lchild);
    btPostfixPrint(t->rchild);
    llPrint(t->data);
}

/*
 * Function that free the tree from memory
*/
void btClearTree(btnode** t){
    if (!t){
        NULLARGUMENT("btClearTree");
    }
    if (!*t)
        return;
    btClearTree(&(*t)->lchild);
    btClearTree(&(*t)->rchild);
    llClearList(&(*t)->data);
    free(*t);
    *t = NULL;
}



#endif
