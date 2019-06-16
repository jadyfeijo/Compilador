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
#define SYMBOL_LIT_STRING 8
#define SYMBOL_IDENTIFIER 276

#define SYMBOL_VAR 5
#define SYMBOL_FUN 6
#define SYMBOL_VET 7

#define SYMBOL_DATATYPE_ERROR 52
#define SYMBOL_DATATYPE_INT 45
#define SYMBOL_DATATYPE_FLOAT 46
#define SYMBOL_DATATYPE_BYTE 47
#define SYMBOL_DATATYPE_BOOL 48
#define SYMBOL_DATATYPE_STRING 49
#define SYMBOL_DATATYPE_CHAR 4


typedef struct hash_node
{
    int type;
    int datatype;
    int numparams;
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

NODE* makeTemp(void);
NODE* makeLabel(void);

#endif