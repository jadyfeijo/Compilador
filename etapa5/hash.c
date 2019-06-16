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
    
    switch(type){
		case SYMBOL_LIT_INT: newnode->datatype = SYMBOL_DATATYPE_INT; break;
		case SYMBOL_LIT_FLOAT: newnode->datatype = SYMBOL_DATATYPE_FLOAT; break;
		case SYMBOL_LIT_CHAR: newnode->datatype = SYMBOL_DATATYPE_BYTE; break;
		case SYMBOL_LIT_STRING: newnode->datatype = SYMBOL_DATATYPE_STRING; break;
	}

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

NODE* makeTemp(void)
{
    static int serialNumber = 0;
    static char buffer[64] = "";

    sprintf(buffer,"myTemp%d",serialNumber++);
    return hashInsert(SYMBOL_IDENTIFIER,buffer);
}

NODE* makeLabel(void)
{
    static int serialNumber = 0;
    static char buffer[64] = "";

    sprintf(buffer,"myLabel%d",serialNumber++);
    return hashInsert(SYMBOL_IDENTIFIER,buffer);
}