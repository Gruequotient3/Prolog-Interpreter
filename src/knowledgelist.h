#ifndef KNOWLEDGE_LIST_H
#define KNOWLEDGE_LIST_H


typedef struct klist_t klist;
typedef struct klnode_t klnode;


struct klist_t{
    char* name;
    int arity;
    struct klnode_t* first;
    struct klnode_t* last;
};

struct klnode_t{
    char** data;
    int size;
    struct klnode_t* next;
};

klist* klNewList(char* name, int arity, klnode* node);
klnode* klNewNode(char** data, int size);

void klInsert(klist* list, klnode** pos, klnode* node);
void klPushFront(klist* list, klnode* node);
void klPushBack(klist* list, klnode* node);

char** klPopFront(klist* list);
char** klPopBack(klist* list);

int klExist(klist* list, char** data, int size);

void klPrint(klist* list);

void klClearNode(klnode* node);
void klClearList(klist** l);



#endif
