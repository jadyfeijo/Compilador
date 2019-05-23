//Eduarda Trindade 274709
//Jady Feijó 230210

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <string.h>

#define HASH_SIZE 997

#define SYMBOL_LITINT 1
#define SYMBOL_IDENTIFIER 2
#define SYMBOL_VAR 3
#define SYMBOL_FUN 4

typedef struct hash_node
{
    int type;
    char *text;
    struct hash_node *next;      
} NODE;

NODE *Table[HASH_SIZE];

void hashInit(void);
int hashAddress(char *text);
NODE* hashFind(char *text);
NODE* hashInsert(int type, char *text);
void hashPrint(void);

#endif