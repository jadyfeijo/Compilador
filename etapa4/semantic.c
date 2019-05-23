#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

//PROTOTYPES

void setAndCheckRedeclared(AST *node)
{
    int i;

    if(node == 0)
        return;

    for(i=0; i < MAX_SONS; ++i)
        setAndCheckRedeclared(node->son[i]);

    switch (node->type)
    {
        case AST_VARDEC:
            if(node->symbol->type == SYMBOL_IDENTIFIER)
            {
                node->symbol->type = SYMBOL_VAR;
            }
            else
            {
                fprintf(stderr,"SEMANTIC ERROR: Identifier %s redeclared\n",node->symbol->text);
            }
            break;

        case AST_DECFUNC:
            if(node->symbol->type == SYMBOL_IDENTIFIER)
            {
                node->symbol->type = SYMBOL_FUN;
            }
            else
            {
                fprintf(stderr,"SEMANTIC ERROR: Identifier %s redeclared\n",node->symbol->text);
            }
            break;
    
        default:
            break;
    }
}