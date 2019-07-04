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

    fprintf(stderr,"\n");
    for (i = 0; i < HASH_SIZE; ++i)
        for(node = Table[i]; node; node = node->next)
            fprintf(stderr,"Table[%d] has %s of type %d and datatype %d\n",i,node->text,node->type,node->datatype);
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
    return hashInsert(SYMBOL_TEMP,buffer);
}

NODE* makeLabel(void)
{
    static int serialNumber = 0;
    static char buffer[64] = "";

    sprintf(buffer,"myLabel%d",serialNumber++);
    return hashInsert(SYMBOL_LABEL,buffer);
}

void hashPrintAsm(FILE *fout)
{
    int i,numLabels = 0;
    NODE *node;

    for(i=0; i<HASH_SIZE; i++)
    {
        for(node = Table[i]; node; node=node->next)
        {
            if((node->type != SYMBOL_FUN) && (node->type != SYMBOL_LABEL))

            switch (node->type)
            {
            case SYMBOL_TEMP:
                fprintf(fout,"\n_%s:\t.long\t0\n",node->text);
                break;
            case SYMBOL_LIT_INT:
                fprintf(fout,"\n_%s:\t.long\t%d\n",node->text,convertIntegers(node->text));
                break;
            case SYMBOL_LIT_STRING:
                fprintf(fout,"\n_%s:\t.string\t%s\n",node->text,node->text);
                break;
            default:
                fprintf(fout,"\n\t.globl	_%s\n"
	                                 "\t.data\n"
	                                 "\t.type	_%s, @object\n"
	                                 "\t.size	_%s, 4\n"
                                    "_%s:\t.long\t%d\n",
                                    node->text,node->text,node->text,node->text,0);
                break;
            }
        }
    }
}

int convertIntegers(char *text)
{
    if(strcmp (text, "O") == 0)
        return 0;
    if(strcmp (text, "I") == 0)
        return 1;
    if(strcmp (text, "H") == 0)
        return 2;
    if(strcmp (text, "G") == 0)
        return 3;
    if(strcmp (text, "F") == 0)
        return 4;
    if(strcmp (text, "E") == 0)
        return 5;
    if(strcmp (text, "D") == 0)
        return 6;
    if(strcmp (text, "C") == 0)
        return 7;
    if(strcmp (text, "B") == 0)
        return 8;
    if(strcmp (text, "A") == 0)
        return 9;
    return 0;
}