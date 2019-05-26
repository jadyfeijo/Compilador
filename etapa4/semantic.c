#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

//PROTOTYPES

void setAndCheckRedeclared(AST *node)
{
    int i;
    AST *aux=NULL;

    if(node == 0)
        return;

    for(i=0; i < MAX_SONS; ++i)
        setAndCheckRedeclared(node->son[i]);

    if(node->type == AST_VARDEC || node->type == AST_VETDEC || node->type == AST_DECFUNC_VOID || node->type == AST_DECFUNC)
    {
        if(node->symbol->type != SYMBOL_IDENTIFIER)
            fprintf(stderr,"SEMANTIC ERROR: Identifier %s redeclared type=%d \n",node->symbol->text,node->symbol->type);


        else
        {
            
            switch (node->type)
            {
                case AST_VARDEC: node->symbol->type = SYMBOL_VAR; break;
                case AST_VETDEC: node->symbol->type = SYMBOL_VET; break;
                case AST_DECFUNC_VOID: node->symbol->type = SYMBOL_FUN; break;
    
                case AST_DECFUNC:
                {
                    if(node->son[1]->symbol->type != SYMBOL_IDENTIFIER) 
                        fprintf(stderr,"SEMANTIC ERROR: Identifier %s redeclared\n",node->son[1]->symbol->text);

                    else
                    {
                      switch(node->son[1]->son[0]->type) //tipos da lista de parametros
                      {
                          case AST_INT: node->son[1]->symbol->datatype = SYMBOL_DATATYPE_INT;
                          case AST_FLOAT: node->son[1]->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
                          case AST_BYTE: node->son[1]->symbol->datatype = SYMBOL_DATATYPE_BYTE;
                          default: break;
                      }
                      node->son[1]->symbol->type= SYMBOL_VAR;
                    }
                    node->symbol->type = SYMBOL_FUN;

                    if(node->son[1]->son[1] !=NULL)
                    {
                        aux = node->son[1];

                        while(aux->son[1]!=NULL) //continuação da lista de parametros
                        {
                            aux=aux->son[1]->son[0];
                            switch (aux->son[0]->type)
                            {
                                case AST_INT: aux->symbol->datatype = SYMBOL_DATATYPE_INT;
                                case AST_FLOAT: aux->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
                                case AST_BYTE: aux->symbol->datatype = SYMBOL_DATATYPE_BYTE;
                                default: break;
                            }

                            if (aux->symbol->type !=SYMBOL_IDENTIFIER)
                                fprintf(stderr,"SEMANTIC ERROR: Identifier %s redeclared\n",aux->symbol->text);

                            aux->symbol->type = SYMBOL_VAR;
                            
                        }
                    }
                    
                    break;
                 }
                    default: break;
            }
        }

        switch (node->son[0]->type)
        {
            case AST_INT: node->symbol->datatype = SYMBOL_DATATYPE_INT;
            case AST_FLOAT: node->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
            case AST_BYTE: node->symbol->datatype = SYMBOL_DATATYPE_BYTE;
            default: break;
        }

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