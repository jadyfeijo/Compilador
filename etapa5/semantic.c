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
                if(node->son[0]->type == AST_DATATYPE_INT)
                    node->symbol->datatype = SYMBOL_DATATYPE_INT;
                if(node->son[0]->type == AST_DATATYPE_CHAR)
                    node->symbol->datatype = SYMBOL_DATATYPE_CHAR;
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
                if(node->son[0]->type == AST_DATATYPE_INT)
                    node->symbol->datatype = SYMBOL_DATATYPE_INT;
                if(node->son[0]->type == AST_DATATYPE_CHAR)
                    node->symbol->datatype = SYMBOL_DATATYPE_CHAR;
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

void checkOperands(AST *node)
{
    int i;

    if(node == 0)
        return;

    for(i = 0; i < MAX_SONS; ++i)
        checkOperands(node->son[i]);

    switch(node->type)
    {
        case AST_ADD:
        if(
            ((node->son[0]->type != AST_ADD) && 
            (node->son[0]->type != AST_SUB) &&
            (node->son[0]->type != AST_SYMBOL))
            ||
            ((node->son[0]->type == AST_SYMBOL) &&
            (node->son[0]->symbol->type == SYMBOL_FUN))
            ||
            ((node->son[0]->type == AST_SYMBOL) &&
            (node->son[0]->symbol->type == SYMBOL_VAR) &&
            (node->son[0]->symbol->datatype != SYMBOL_DATATYPE_INT))
        )
        fprintf(stderr,"Invalid first operand of +\n");
        break;
    }
}