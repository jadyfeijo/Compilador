//Eduarda Trindade 274709
//Jady Feijó 230210

#include "hash.h"

void hashInit(void)
{
    int i;

    for (i = 0; i < HASH_SIZE; ++i)
        Table[i] = 0;
}

int hashAddress(char *text)
{
    int i;
    int address = 1;

    for(i = 0; i < strlen(text); ++i)
        address = (address * text[i]) % HASH_SIZE + 1;
    
    return address - 1;
}

NODE* hashFind(char *text)
{
   NODE *node;
   int address = hashAddress(text);

   for(node = Table[address]; node; node = node->next)
        if(strcmp(text,node->text) == 0)
            return node;

    return 0; 
}

NODE* hashInsert(int type, char *text)
{
    NODE *newnode;
    int address = hashAddress(text);

    if ((newnode = hashFind(text)) != 0)
        return newnode;

    newnode = (NODE*) calloc(1,sizeof(NODE));
    newnode->type = type;
    newnode->text = calloc(strlen(yytext) + 1, sizeof(char));

    strcpy(newnode->text,text);
    newnode->next = Table[address];
    Table[address] = newnode;

    return newnode;
}

void hashPrint(void)
{
    NODE *node;
    int i;

    for (i = 0; i < HASH_SIZE; ++i)
        for(node = Table[i]; node; node = node->next)
            fprintf(stderr," Table[%d] has %s\n",i,node->text);

}

void hashCheckUndeclared(void)
{
    int i;

    NODE *node;

    for(i = 0; i < HASH_SIZE; ++i)
        for(node = Table[i]; node; node=node->next)
            if(node->type == SYMBOL_IDENTIFIER)
            {
                fprintf(stderr," Undeclared identifier %s\n", node->text);
            }
}