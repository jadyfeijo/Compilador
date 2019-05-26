#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

int semanticError=0;
AST *nodeDeclared=NULL;

void functionValidation (AST *node);


void setAndCheckRedeclared(AST *node)
{
    int i;
    AST *aux=NULL;

    nodeDeclared=node;


    if(node == 0)
        return;

    for(i=0; i < MAX_SONS; ++i)
        setAndCheckRedeclared(node->son[i]);

    if(node->type == AST_VARDEC || node->type == AST_VETDEC || node->type == AST_DECFUNC_VOID || node->type == AST_DECFUNC)
    {
        if(node->symbol->type != SYMBOL_IDENTIFIER)
        {
            fprintf(stderr,"SEMANTIC ERROR: Identifier %s redeclared type=%d \n",node->symbol->text,node->symbol->type);
            semanticError=1;
        }

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
                    {
                        fprintf(stderr,"SEMANTIC ERROR: Identifier %s redeclared\n",node->son[1]->symbol->text);
                        semanticError=1;
                    }

                    else
                    {
                      switch(node->son[1]->son[0]->type) //tipos da lista de parametros
                      {
                          case AST_INT: node->son[1]->symbol->datatype = SYMBOL_DATATYPE_INT; break;
                          case AST_FLOAT: node->son[1]->symbol->datatype = SYMBOL_DATATYPE_FLOAT;break;
                          case AST_BYTE: node->son[1]->symbol->datatype = SYMBOL_DATATYPE_BYTE;break;
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
                                case AST_INT: aux->symbol->datatype = SYMBOL_DATATYPE_INT; break;
                                case AST_FLOAT: aux->symbol->datatype = SYMBOL_DATATYPE_FLOAT; break;
                                case AST_BYTE: aux->symbol->datatype = SYMBOL_DATATYPE_BYTE; break;
                                default: break;
                            }

                            if (aux->symbol->type !=SYMBOL_IDENTIFIER)
                            {
                                fprintf(stderr,"SEMANTIC ERROR: Identifier %s redeclared\n",aux->symbol->text);
                                semanticError=1;
                            }
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
            case AST_INT: node->symbol->datatype = SYMBOL_DATATYPE_INT; break;
            case AST_FLOAT: node->symbol->datatype = SYMBOL_DATATYPE_FLOAT; break;
            case AST_BYTE: node->symbol->datatype = SYMBOL_DATATYPE_BYTE; break;
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

        case AST_ASSIGN:
        if(node->symbol->type !=SYMBOL_VAR)
            fprintf(stderr,"SEMANTIC ERROR: Symbol %s must be scalar!\n", node->symbol->text);
            
        if(node->symbol->datatype !=node->son[0]->symbol->datatype)
        {
            if(node->symbol->datatype==SYMBOL_DATATYPE_FLOAT || node->son[0]->symbol->datatype==SYMBOL_DATATYPE_FLOAT)
            {fprintf(stderr,"SEMANTIC ERROR: Imcompatible type in assign %s = %s \n",node->symbol->text,node->son[0]->symbol->text);
            semanticError=1;}

        }
        break;

        case AST_ASSIGNARRAY:
        if(node->symbol->datatype !=node->son[1]->symbol->datatype)
        {
            if(node->symbol->datatype==SYMBOL_DATATYPE_FLOAT || node->son[1]->symbol->datatype==SYMBOL_DATATYPE_FLOAT)
            {fprintf(stderr,"SEMANTIC ERROR: Imcompatible type in assign %s[%s] = %s",node->symbol->text,node->son[0]->symbol->text,node->son[1]->symbol->text);
            semanticError=1;
            break;
            }

        }
        if(node->son[0]->symbol->datatype!=SYMBOL_DATATYPE_INT && node->son[0]->symbol->datatype!=SYMBOL_DATATYPE_BYTE)
        {
            fprintf(stderr,"SEMANTIC ERROR: Invalid Index type in assign %s[%s] = %s\n",node->symbol->text,node->son[0]->symbol->text,node->son[1]->symbol->text);
            semanticError=1;
        }
        break;

        case AST_FUNCCALL:
                  fprintf(stderr,"Passou na func %s \n",node->symbol->text);

        if(node->symbol->type !=SYMBOL_FUN)
        {
            fprintf(stderr,"SEMANTIC ERROR: Identifier %s is not a function\n",node->symbol->text);
            semanticError=1;

        }
      //  functionValidation(node);
       /* else
        {
            switch (functionValidation(node))
            {
            
            
            default:
                break;
            }
        }*/
        
break;

default:break;

    }
}

/*void functionValidation (AST *node)
{

    

}*/