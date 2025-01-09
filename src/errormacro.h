#ifndef ERROR_MACRO_H
#define ERROR_MACRO_H



#define INVALIDSYNTAX(line, string) \
    printf("Error : Invalid syntax at line %d : \n", line);\
    printf("%s\n", string);\
    exit(1);

#define INVALIDSYNTAXQ(string) \
    printf("Error : Invalid syntax\n");\
    printf("%s\n", string);\
    return 0;

#define NULLARGUMENT(functionName) \
    printf("Error : Wrong argument (NULL argument) in %s\n", functionName);\
    exit(1);

#define FAILEDALLOCATEMEMORY(functionName)\
    printf("Error : Failed to allocate memory in %s\n", functionName);\
    exit(1);
#endif
