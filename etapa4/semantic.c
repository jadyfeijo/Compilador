#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

int semanticError=0;
AST *nodeDeclared;

int arithmeticOperation(int nodeType);
int expressionTypes(int op1,int op2);
int getType(AST* node);
int functionValidation (AST* nodeDeclared, AST *node);
int validReturn(AST* nodeDeclared,AST *node);

void setAndCheckRedeclared(AST *node)
{
    int i;
    AST *aux = NULL;

    if(nodeDeclared==NULL)
        nodeDeclared = node;

    if(node == 0)
        return;

    for(i=0; i < MAX_SONS; ++i)
        setAndCheckRedeclared(node->son[i]);

    if(node->type == AST_VARDEC || node->type == AST_VETDEC || node->type == AST_DECFUNC_VOID || node->type == AST_DECFUNC)
    {
        if(node->symbol->type != SYMBOL_IDENTIFIER)
        {
            fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s redeclared type=%d \n", node->lineNumber,node->symbol->text,node->symbol->type);
            semanticError++;
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
                        fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s redeclared\n",node->lineNumber,node->son[1]->symbol->text);
                        semanticError++;
                    }
                    else
                    {
                      switch(node->son[1]->son[0]->type)
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

                        while(aux->son[1] != NULL)
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
                                fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s redeclared\n",aux->lineNumber,aux->symbol->text);
                                semanticError++;
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
            if(getType(node) == SYMBOL_DATATYPE_ERROR)  
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Incompatible type operands.\n",node->lineNumber);
                semanticError++;
            }                
        break;
       
        case AST_ASSIGN:
            if(node->symbol->type != SYMBOL_VAR)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Symbol %s must be scalar.\n",node->lineNumber, node->symbol->text);
                semanticError++;
            }
            if(node->symbol->datatype != getType(node->son[0]))  
            {
                if(node->symbol->datatype==SYMBOL_DATATYPE_FLOAT || getType(node->son[0])==SYMBOL_DATATYPE_FLOAT ||
                node->symbol->datatype==SYMBOL_DATATYPE_ERROR ||getType(node->son[0])==SYMBOL_DATATYPE_ERROR ||
                node->symbol->datatype==SYMBOL_DATATYPE_BOOL ||getType(node->son[0])==SYMBOL_DATATYPE_BOOL)
                {
                    fprintf(stderr,"SEMANTIC ERROR in line %d. Incompatible type in assignment.\n",node->lineNumber);
                    semanticError++;
                }

            }
        break;

        case AST_ASSIGNARRAY:
            if(node->symbol->type != SYMBOL_VET)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s is not a vector.\n",node->lineNumber,node->symbol->text);
                semanticError++;
            }

            if(node->symbol->datatype != getType(node->son[1]))
            {
                if(node->symbol->datatype==SYMBOL_DATATYPE_FLOAT || getType(node->son[0])==SYMBOL_DATATYPE_FLOAT ||
                node->symbol->datatype==SYMBOL_DATATYPE_ERROR ||getType(node->son[0])==SYMBOL_DATATYPE_ERROR ||
                node->symbol->datatype==SYMBOL_DATATYPE_BOOL ||getType(node->son[0])==SYMBOL_DATATYPE_BOOL)           
                {
                    fprintf(stderr,"SEMANTIC ERROR in line %d. Imcompatible type in assignment %s[%s] = %s.",node->lineNumber,node->symbol->text,node->son[0]->symbol->text,node->son[1]->symbol->text);
                    semanticError++;
                    break;
                }

            }
            if(getType(node->son[0])!=SYMBOL_DATATYPE_INT && getType(node->son[0])!=SYMBOL_DATATYPE_BYTE)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Invalid Index type in assignment.\n",node->lineNumber);
                semanticError++;
            }
        break;

        case AST_IFT:
        case AST_IFTE:
            if(getType(node->son[0]) != SYMBOL_DATATYPE_BOOL)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. If condition type must be BOOL.\n",node->lineNumber);
                semanticError++;
            }
        break;

       case AST_LOOP:
            if(getType(node->son[0]) != SYMBOL_DATATYPE_BOOL)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Loop condition type must be BOOL.\n",node->lineNumber);
                semanticError++;
            }
            break;
        
        case AST_ARRAY:
            if(node->symbol->type != SYMBOL_VET)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s is not a vector.\n",node->lineNumber,node->symbol->text);
                semanticError++;
            }
        break;
        
        case AST_DECFUNC:
            if(validReturn(nodeDeclared,node)==0)
            {
                    fprintf(stderr, "SEMANTIC ERROR in line %d. Invalid return type in function %s.\n",node->lineNumber,node->symbol->text);
                    semanticError++;
            }
        break;

        case AST_FUNCCALL:

        if (node->symbol->type != SYMBOL_FUN)
        {
            fprintf(stderr, "SEMANTIC ERROR in line %d. Identifier %s is not a function.\n",node->lineNumber,node->symbol->text);
            semanticError++;
        }

        else
        {
            switch (functionValidation(nodeDeclared, node))
            {

            case 1:
                break; //parametros certos
            case 2:
                fprintf(stderr, "SEMANTIC ERROR in line %d. Incompatible parameter type in function %s.\n",node->lineNumber,node->symbol->text);
                semanticError++;
                break;

            case 3:
                fprintf(stderr, "SEMANTIC ERROR in line %d. Invalid number of parameters in function %s. \n",node->lineNumber, node->symbol->text);
                semanticError++;
                break;
            default:
                break;
            }
        }
        break;
    
    
    default:
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
			return getType(node->son[0]);
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

int functionValidation(AST *nodeDeclared, AST *node)
{
    AST *aux = nodeDeclared;

    if ((nodeDeclared->type == AST_DECFUNC || nodeDeclared->type == AST_DECFUNC_VOID) && strcmp(nodeDeclared->symbol->text, node->symbol->text) == 0)
    {
        AST *declaration_param = NULL;
        int dec_type, call_type;

        if (nodeDeclared->type == AST_DECFUNC)
            declaration_param = nodeDeclared->son[1];

        AST *funccall_param = node->son[0];

        if (declaration_param == NULL && funccall_param == NULL)
            return 1;
        if (declaration_param == NULL || funccall_param == NULL)
            return 3;

        while (declaration_param != NULL && funccall_param != NULL)
        {
            switch (declaration_param->son[0]->type)
            {
            case AST_INT:
                dec_type = SYMBOL_DATATYPE_INT;
                break;

            case AST_FLOAT:
                dec_type = SYMBOL_DATATYPE_FLOAT;
                break;

            case AST_BYTE:
                dec_type = SYMBOL_DATATYPE_BYTE;
                break;

            default:
                dec_type = SYMBOL_DATATYPE_ERROR;
                break;
            }

            call_type = getType(funccall_param->son[0]);

            // if(expressionTypes(dec_type,call_type)==SYMBOL_DATATYPE_ERROR) return 2;
            if (dec_type != call_type)
            {
                if ((dec_type == SYMBOL_DATATYPE_BYTE && call_type == SYMBOL_DATATYPE_INT) || (dec_type == SYMBOL_DATATYPE_INT && call_type == SYMBOL_DATATYPE_BYTE))
                    return 1;
                else
                    return 2;
            }
            if (declaration_param->son[1])
                declaration_param = declaration_param->son[1]->son[0];

            else
            {
                declaration_param = NULL;
            }

            if (funccall_param->son[1])
            {
                funccall_param = funccall_param->son[1]->son[0];
            }
            else
            {
                funccall_param = NULL;
            }
        }

        /*if(declaration_param==NULL && funccall_param==NULL) return 1;

        return 3;
            */
    }
    else
    {
        int number_sons = 0;

        for (number_sons = 0; number_sons < 4; number_sons++)
        {
            if (nodeDeclared->son[number_sons] != NULL)
            {
                int found;
                found = functionValidation(nodeDeclared->son[number_sons], node);
                if (found != 5)
                    return found;
            }
        }
    }

    return 5;
}

int validReturn(AST* nodeDeclared,AST *node)
{
    int dec_type;
    if (nodeDeclared->type==AST_RETURN)
    {
        dec_type=node->symbol->datatype;
        int return_type=getType(nodeDeclared->son[0]);

        if(dec_type!=return_type)
            if ((dec_type == SYMBOL_DATATYPE_BYTE && return_type == SYMBOL_DATATYPE_INT) || (dec_type == SYMBOL_DATATYPE_INT && return_type == SYMBOL_DATATYPE_BYTE))
                    return 1;
               
        else return 0;
        
        else return 0;
    }
    else
    {
        int number_sons = 0;

        for (number_sons = 0; number_sons < 4; number_sons++)
        {
            if (nodeDeclared->son[number_sons] != NULL)
            {
                int found;
                found = validReturn(nodeDeclared->son[number_sons], node);
                if (found != 5)
                    return found;
            }
        }
    }

    return 5;

}
