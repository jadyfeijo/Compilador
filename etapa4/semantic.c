#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

int semanticError=0;
AST *nodeDeclared=NULL;

void functionValidation (AST *node);


void setAndCheckRedeclared(AST *node)
{
    int i;
    AST *aux = NULL;

    nodeDeclared = node;

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

                    if(node->son[1]->son[1] != NULL)
                    {
                        aux = node->son[1];

                        while(aux->son[1] != NULL) //continuação da lista de parametros
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
        case AST_SYMBOL_INT:
            node->symbol->datatype = SYMBOL_DATATYPE_INT;
            node->symbol->type = SYMBOL_LIT_INT; 
        break;

        case AST_SYMBOL_FLOAT:
            node->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
            node->symbol->type = SYMBOL_LIT_FLOAT; 
        break;

        case AST_SYMBOL_CHAR:
            node->symbol->datatype = SYMBOL_DATATYPE_CHAR;
            node->symbol->type = SYMBOL_LIT_CHAR; 
        break;
        
        case AST_ADD:
        case AST_SUB:
        case AST_MULT:
        case AST_DIV:
           if((!arithmeticOperation(node->son[0]->type) &&
                (node->son[0]->type != AST_SYMBOL))
                ||
                ((node->son[0]->type == AST_SYMBOL) &&
                (node->son[0]->symbol->type == SYMBOL_FUN))
                ||
                ((node->son[0]->type == AST_SYMBOL) &&
                (node->son[0]->symbol->type == SYMBOL_VAR) &&
                ((node->son[0]->symbol->datatype != SYMBOL_DATATYPE_INT) && (node->son[0]->symbol->datatype !=  SYMBOL_DATATYPE_BYTE))))
                fprintf(stderr,"SEMANTIC ERROR in line %d. Invalid first operand.\n",node->lineNumber);
            if((!arithmeticOperation(node->son[1]->type) &&
                (node->son[1]->type != AST_SYMBOL))
                ||
                ((node->son[1]->type == AST_SYMBOL) &&
                (node->son[1]->symbol->type == SYMBOL_FUN))
                ||
                ((node->son[1]->type == AST_SYMBOL) &&
                (node->son[1]->symbol->type == SYMBOL_VAR) &&
                ((node->son[1]->symbol->datatype != SYMBOL_DATATYPE_INT) && (node->son[1]->symbol->datatype !=  SYMBOL_DATATYPE_BYTE))))
                fprintf(stderr,"SEMANTIC ERROR in line %d. Invalid second operand.\n",node->lineNumber);                          
        break;
       
        case AST_ASSIGN:
            if(node->symbol->type != SYMBOL_VAR)
                fprintf(stderr,"SEMANTIC ERROR in line %d. Symbol %s must be scalar!\n",node->lineNumber, node->symbol->text);

            if(node->symbol->datatype != getType(node->son[0]))  
            {
                if(node->symbol->datatype == SYMBOL_DATATYPE_FLOAT || getType(node->son[0]) == SYMBOL_DATATYPE_FLOAT)
                {
                    fprintf(stderr,"SEMANTIC ERROR in line %d. Incompatible type in assignment. \n",node->lineNumber);
                    semanticError=1;
                }

            }
        break;

        case AST_ASSIGNARRAY:
            if(node->symbol->datatype !=getType(node->son[1]))
            {
                if(node->symbol->datatype == SYMBOL_DATATYPE_FLOAT || node->son[1]->symbol->datatype == SYMBOL_DATATYPE_FLOAT)
                {
                    fprintf(stderr,"SEMANTIC ERROR in line %d. Incompatible type in assignment. \n",node->lineNumber);
                    semanticError=1;
                    break;
                }

            }
            if(node->son[0]->symbol->datatype != SYMBOL_DATATYPE_INT && node->son[0]->symbol->datatype != SYMBOL_DATATYPE_BYTE)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Invalid Index type in assignment. \n",node->lineNumber);
                semanticError=1;
            }
        break;
        
        case AST_FUNCCALL:
            fprintf(stderr,"Passou na func %s \n",node->symbol->text);

            if(node->symbol->type != SYMBOL_FUN)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s is not a function\n",node->lineNumber,node->symbol->text);
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
        
        default: 
            //fprintf(stderr,"\ncheckOperands() DEFAULT: node type = %d \n", node->type);
        break;

    }
}

int arithmeticOperation(int nodeType)
{
    return (nodeType == AST_ADD || nodeType == AST_SUB || nodeType == AST_MULT || nodeType == AST_DIV);
}

int getType(AST* node) 
{
	int op1, op2;
	
	switch(node->type) 
	{
		case AST_SYMBOL: 
        case AST_SYMBOL_INT: 
        case AST_SYMBOL_FLOAT : 
        case AST_SYMBOL_CHAR: 
		case AST_ARRAY:
		case AST_FUNCCALL:
			return node->symbol->datatype;
		case AST_PARENTH:
			return getType(node);
		case AST_ADD:
		case AST_SUB:
		case AST_DIV:
		case AST_MULT:
				op1 = getType(node->son[0]);
			    op2 = getType(node->son[1]);
				return expressionTypes(op1,op2);
		case AST_LE:
		case AST_GE:
		case AST_EQ:
		case AST_DIF:
		case AST_AND:
		case AST_OR: 
		case AST_GREATER:
		case AST_LESS: 
        case AST_NOT:
			return SYMBOL_DATATYPE_BOOL;
	}
}

int expressionTypes(int op1,int op2)
{
    switch (op1)
    {
    case SYMBOL_DATATYPE_BOOL:
        switch (op2)
        {
        case SYMBOL_DATATYPE_BOOL:
            return SYMBOL_DATATYPE_BOOL;

        default: return SYMBOL_DATATYPE_ERROR;
        }
        
    case SYMBOL_DATATYPE_BYTE:
        switch (op2)
        {
        case SYMBOL_DATATYPE_BYTE:
        case SYMBOL_DATATYPE_INT:
        case SYMBOL_DATATYPE_CHAR:
            return SYMBOL_DATATYPE_INT;
        
        case SYMBOL_DATATYPE_FLOAT:
            return SYMBOL_DATATYPE_FLOAT;

        default: return SYMBOL_DATATYPE_ERROR;        
       
        }    

    case SYMBOL_DATATYPE_INT:
        switch (op2)
        {
        case SYMBOL_DATATYPE_BYTE:
        case SYMBOL_DATATYPE_INT:
        case SYMBOL_DATATYPE_CHAR:
            return SYMBOL_DATATYPE_INT;

        case SYMBOL_DATATYPE_FLOAT:
            return SYMBOL_DATATYPE_FLOAT;

        default: return SYMBOL_DATATYPE_ERROR;        
       
        }    

    case SYMBOL_DATATYPE_CHAR:
        switch (op2)
        {
        case SYMBOL_DATATYPE_BYTE:
        case SYMBOL_DATATYPE_INT:
            return SYMBOL_DATATYPE_INT;

        case SYMBOL_DATATYPE_CHAR:
            return SYMBOL_DATATYPE_CHAR;

        case SYMBOL_DATATYPE_FLOAT:
            return SYMBOL_DATATYPE_FLOAT;

        default: return SYMBOL_DATATYPE_ERROR;        
       
        }   

    case SYMBOL_DATATYPE_FLOAT:
        switch (op2)
        {
        case SYMBOL_DATATYPE_BOOL:
            return SYMBOL_DATATYPE_ERROR;

        case SYMBOL_DATATYPE_ERROR:
            return SYMBOL_DATATYPE_ERROR;

        default: return SYMBOL_DATATYPE_FLOAT;
        }
    
    default: return SYMBOL_DATATYPE_ERROR;
    }
}
