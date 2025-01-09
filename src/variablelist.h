#ifndef VARIABLE_LIST_H
#define VARIABLE_LIST_H

typedef struct vlist_t vlist;
typedef struct vlnode_t vlnode;

struct vlist_t{
    struct vlnode_t* first;
    struct vlnode_t* last;
};

struct vlnode_t{
    char* name;
    char* data;
    struct vlnode_t* next;
};

vlist* vlNewList(vlnode* node);
vlnode* vlNewNode(char* name, char* data);

void vlInsert(vlist* list, vlnode** pos, vlnode* node);
void vlPushFront(vlist* list, vlnode* node);
void vlPushBack(vlist* list, vlnode* node);

char* vlPopFront(vlist* list);
char* vlPopBack(vlist* list);

int vlExist(vlist* list, char* name);

void vlPrint(vlist* list);

void vlClearNode(vlnode* node);
void vlClearList(vlist** l);



#endif
