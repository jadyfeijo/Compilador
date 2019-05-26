//Eduarda Trindade 274709
//Jady Feijó 230210

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <string.h>

#define HASH_SIZE 997

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_FLOAT 2
#define SYMBOL_LIT_BYTE 3
#define SYMBOL_LIT_CHAR 4
#define SYMBOL_IDENTIFIER 276
//const int SYMBOL_IDENTIFIER = TK_IDENTIFIER;

#define SYMBOL_VAR 5
#define SYMBOL_FUN 6
#define SYMBOL_VET 7

#define SYMBOL_DATATYPE_INT 1
#define SYMBOL_DATATYPE_BYTE 2
#define SYMBOL_DATATYPE_FLOAT 3
#define SYMBOL_DATATYPE_CHAR 4
#define SYMBOL_DATATYPE_STRING 5
#define SYMBOL_DATATYPE_BOOL 6


typedef struct hash_node
{
    int type;
    int datatype;
    char *text;
    struct hash_node *next;      
} NODE;

NODE *Table[HASH_SIZE];

void hashInit(void);
int hashAddress(char *text);
NODE* hashFind(char *text);
NODE* hashInsert(int type, char *text);
void hashPrint(void);
void hashCheckUndeclared(void);

#endif