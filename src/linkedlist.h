#ifndef LINKED_LIST_H
#define LINKED_LIST_H


typedef struct llist_t llist;
typedef struct llnode_t llnode;


struct llist_t{
    struct llnode_t* first;
    struct llnode_t* last;
};

struct llnode_t{
    char* data;
    struct llnode_t* next;
};

llist* llNewList(llnode* node);
llnode* llNewNode(char* data);

void llInsert(llist* list, llnode** pos, llnode* node);
void llPushFront(llist* list, llnode* node);
void llPushBack(llist* list, llnode* node);


char* llPopFront(llist* list);
char* llPopBack(llist* list);

void llPrint(llist* list);


void llClearNode(llnode* node);
void llClearList(llist** l);



#endif
