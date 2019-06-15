//Eduarda Trindade 274709
//Jady Feijó 230210

#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

int semanticError = 0;
AST *nodeDeclared;


void setTypes(AST* node);
int numParamsFunc(AST* node);
int checkVet(AST* node, int datatype);
int getType(AST* node);
int expressionTypes(int op1,int op2);
int functionValidation (AST* nodeDeclared, AST *node);
int validReturn(AST *nodeDec,AST *node);
int checkParams(AST* node);

void setAndCheckRedeclared(AST *node)
{
    int i;

    if(nodeDeclared==NULL)
		nodeDeclared=node;

	if (node == 0) 
        return;
	
	for (i = 0; i < MAX_SONS; ++i)
		setAndCheckRedeclared(node->son[i]);

	switch(node->type)
    {
		case AST_VARDEC:
			if(node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s redeclared type=%d \n", node->lineNumber,node->symbol->text,node->symbol->type);
                semanticError++;
            }
			else
            {
				node->symbol->type = SYMBOL_VAR;
				setTypes(node);
			}
		break;
		case AST_VETDEC:
			if(node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s redeclared type=%d \n", node->lineNumber,node->symbol->text,node->symbol->type);
                semanticError++;
            }
			else{
				node->symbol->type = SYMBOL_VET;
				setTypes(node);
			}
			break;
		case AST_DECFUNC_VOID:
			if(node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s redeclared type=%d \n", node->lineNumber,node->symbol->text,node->symbol->type);
                semanticError++;
            }
			else{
				node->symbol->type = SYMBOL_FUN;
				node->symbol->numparams = 0;
				setTypes(node);
			}
		break;
        case AST_DECFUNC:
			if(node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s redeclared type=%d \n", node->lineNumber,node->symbol->text,node->symbol->type);
                semanticError++;
            }
			else
            {
				node->symbol->type = SYMBOL_FUN;
				node->symbol->numparams = numParamsFunc(node->son[1]);
				setTypes(node);
			}
		break;
		case AST_DEC_PARAM:
			if(node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s redeclared type=%d \n", node->lineNumber,node->symbol->text,node->symbol->type);
                semanticError++;
            }
			else
            {
				node->symbol->type = SYMBOL_VAR;
				setTypes(node);
			}
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
        case AST_SYMBOL:
            switch (node->symbol->type)
            {
                case SYMBOL_VAR:
                    if(node->symbol->datatype == SYMBOL_DATATYPE_INT)
                    {
                        node->datatype = AST_DATATYPE_INT;
                    }  
                    else if(node->symbol->datatype == SYMBOL_DATATYPE_BYTE){
                        node->datatype = AST_DATATYPE_BYTE;
                    }  
                    else if(node->symbol->datatype == SYMBOL_DATATYPE_FLOAT){
                        node->datatype = AST_DATATYPE_FLOAT;
                    }
                break;
                case SYMBOL_VET:
				    node->datatype = AST_DATATYPE_VET;
                break;
                case SYMBOL_FUN:
				    node->datatype = AST_DATATYPE_FUN;
                break;
                case SYMBOL_LIT_INT:
				    node->datatype = AST_DATATYPE_INT;
                break;
                case SYMBOL_LIT_FLOAT:
				    node->datatype = AST_DATATYPE_FLOAT;
                break;
                case SYMBOL_LIT_CHAR:
				    node->datatype = AST_DATATYPE_BYTE;
                break;
                case SYMBOL_LIT_STRING:
				    node->datatype = AST_DATATYPE_STRING;
                break;
                default:
                break;
            }
        break;
		case AST_VARDEC: 
			if(node->son[1]->symbol != NULL) 
			{	
                if((node->symbol->datatype == SYMBOL_DATATYPE_INT || node->symbol->datatype == SYMBOL_DATATYPE_BYTE) && 
                    (node->son[1]->symbol->datatype != SYMBOL_DATATYPE_INT && node->son[1]->symbol->datatype != SYMBOL_DATATYPE_BYTE))
				{
                    fprintf(stderr,"SEMANTIC ERROR in line %d. Variable %s must recieve int or byte.\n", node->lineNumber,node->symbol->text);
                    semanticError++;
				}
				else if(node->symbol->datatype == SYMBOL_DATATYPE_FLOAT && node->son[1]->symbol->datatype != SYMBOL_DATATYPE_FLOAT)
                {
                    fprintf(stderr,"SEMANTIC ERROR in line %d. Variable %s must recieve float.\n", node->lineNumber,node->symbol->text);
                    semanticError++;
				}
			}
		break;
        case AST_VETDEC:
			if(checkVet(node->son[2], node->symbol->datatype) == 0)
            {
                fprintf(stderr,"SEMANTIC ERROR in line %d. Invalid types in vector declaration\n", node->lineNumber);
                semanticError++;
            }
		break;
		case AST_DECFUNC_VOID:
        case AST_DECFUNC:
        
            if(validReturn(node,node)==0)
            {
                    fprintf(stderr, "SEMANTIC ERROR in line %d. Invalid return type in function %s.\n",node->lineNumber,node->symbol->text);
                    semanticError++;
            }
        
		break;
		case AST_ASSIGN: 
			if(node->symbol->type != SYMBOL_VAR)
			{
                fprintf(stderr,"SEMANTIC ERROR in line %d. Symbol %s must be scalar.\n",node->lineNumber, node->symbol->text);
                semanticError++;
            }
            if(node->symbol->datatype == SYMBOL_DATATYPE_INT || node->symbol->datatype == SYMBOL_DATATYPE_BYTE)
            {
				if(node->son[0] != NULL)
                {
					if(node->son[0]->datatype != AST_DATATYPE_INT && node->son[0]->datatype != AST_DATATYPE_BYTE)
                    {
                        fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s must be assigned to byte or int.\n",node->lineNumber,node->symbol->text);
						semanticError++;
					}
				}
            }	
			else if(node->symbol->datatype == SYMBOL_DATATYPE_FLOAT)
            {
				if(node->son[0] != NULL)
                {
					if(node->son[0]->datatype != AST_DATATYPE_FLOAT)
                    {
                        fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s must be assigned to float.\n",node->lineNumber,node->symbol->text);
						semanticError++;
					}
				}
			}		
			break;
		case AST_ASSIGNARRAY: 
			if(node->symbol->type != SYMBOL_VET)
			{
				fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s is not a vector.\n",node->lineNumber,node->symbol->text);
                semanticError++;
			}

			if(node->son[0]->datatype != AST_DATATYPE_INT && node->son[0]->datatype != AST_DATATYPE_BYTE){
				fprintf(stderr,"SEMANTIC ERROR in line %d. Invalid index type in assignment, must be byte or int.\n",node->lineNumber);
                semanticError++;
			}

            if(node->symbol->datatype == SYMBOL_DATATYPE_INT || node->symbol->datatype == SYMBOL_DATATYPE_BYTE)
            {
				if(node->son[1] != NULL)
                {
					if(node->son[1]->datatype != AST_DATATYPE_INT && node->son[1]->datatype != AST_DATATYPE_BYTE)
                    {
                        fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s must be assigned to byte or int.\n",node->lineNumber,node->symbol->text);
						semanticError++;
					}
				}
            }	
			else if(node->symbol->datatype == SYMBOL_DATATYPE_FLOAT)
            {
				if(node->son[1] != NULL)
                {
					if(node->son[1]->datatype != AST_DATATYPE_FLOAT)
                    {
                        fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s must be assigned to float.\n",node->lineNumber,node->symbol->text);
						semanticError++;
					}
				}
			}		
		break;
        case AST_ARRAY:
			if(node->symbol->datatype == SYMBOL_DATATYPE_INT)
            {
				node->datatype = AST_DATATYPE_INT;
			}  
			else if(node->symbol->datatype == SYMBOL_DATATYPE_BYTE){
				node->datatype = AST_DATATYPE_BYTE;
			}  
			else if(node->symbol->datatype == SYMBOL_DATATYPE_FLOAT){
				node->datatype = AST_DATATYPE_FLOAT;
			}
			
			if(node->symbol->type != SYMBOL_VET)
			{
				fprintf(stderr,"SEMANTIC ERROR in line %d. Identifier %s is not a vector.\n",node->lineNumber,node->symbol->text);
                semanticError++;
				node->datatype = AST_DATATYPE_ERROR;
			}
			if(node->son[0]->datatype != AST_DATATYPE_INT && node->son[0]->datatype != AST_DATATYPE_BYTE){
				fprintf(stderr,"SEMANTIC ERROR in line %d. Invalid index type in array, must be byte or int.\n",node->lineNumber);
				semanticError++;
				node->datatype = AST_DATATYPE_ERROR;
			}
		break;
		case AST_FUNCCALL:	
			if(node->symbol->datatype == SYMBOL_DATATYPE_INT)
            {
				node->datatype = AST_DATATYPE_INT;
			}  
			else if(node->symbol->datatype == SYMBOL_DATATYPE_BYTE){
				node->datatype = AST_DATATYPE_BYTE;
			}  
			else if(node->symbol->datatype == SYMBOL_DATATYPE_FLOAT){
				node->datatype = AST_DATATYPE_FLOAT;
			}

			if(node->symbol->type != SYMBOL_FUN)
			{
				fprintf(stderr, "SEMANTIC ERROR in line %d. Identifier %s is not a function.\n",node->lineNumber,node->symbol->text);
                semanticError++;
				node->datatype = AST_DATATYPE_ERROR;
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
        case AST_READ:
			if(node->symbol->type != SYMBOL_VAR)
			{
				fprintf(stderr,"SEMANTIC ERROR in line %d. Symbol %s must be scalar\n",node->lineNumber, node->symbol->text);
				semanticError++;
			}
			break;
		case AST_PRINT_PARAM:
			if(node->son[0] != NULL)
            {
                if(node->son[0]->type != AST_PRINT_PARAM)
                    if(node->son[0]->datatype != AST_DATATYPE_STRING && node->son[0]->datatype != AST_DATATYPE_INT && node->son[0]->datatype != AST_DATATYPE_FLOAT && node->son[0]->datatype != AST_DATATYPE_BYTE)
                    {
                        semanticError++;
                    }
			}
		break;
        case AST_IFT: 
		case AST_IFTE:	
		case AST_LOOP:	
			if(node->son[0] != NULL)
            {
				if(node->son[0]->datatype != AST_DATATYPE_BOOL)
                {
					fprintf(stderr,"SEMANTIC ERROR in line %d. Condition type must be bool.\n",node->lineNumber);
                    semanticError++;
				}
			}
		break;
		case AST_ADD:
		case AST_SUB:
		case AST_MULT:
		case AST_DIV:
			if(node->son[0] != NULL && node->son[1] != NULL)
            {
				if((node->son[0]->datatype == AST_DATATYPE_FLOAT && node->son[1]->datatype == AST_DATATYPE_FLOAT) || 
                (node->son[0]->datatype == AST_DATATYPE_FLOAT && node->son[1]->datatype == AST_DATATYPE_INT) || 
                (node->son[0]->datatype == AST_DATATYPE_INT && node->son[1]->datatype == AST_DATATYPE_FLOAT))
                {
					node->datatype = AST_DATATYPE_FLOAT;
				}
				else
                {
					if(node->son[0]->datatype == AST_DATATYPE_INT || node->son[1]->datatype == AST_DATATYPE_INT)
                    {
						node->datatype = AST_DATATYPE_INT;
					}
					else
                    {
						node->datatype = AST_DATATYPE_BYTE;
					}	
					if((node->son[0]->datatype != AST_DATATYPE_INT && node->son[0]->datatype != AST_DATATYPE_BYTE) || 
						(node->son[1]->datatype != AST_DATATYPE_INT && node->son[1]->datatype != AST_DATATYPE_BYTE))
                    {
						fprintf(stderr,"SEMANTIC ERROR in line %d. Operators must be int, byte or float. \n", node->lineNumber);
						semanticError++;
						node->datatype = AST_DATATYPE_ERROR;
					}
				}
			}
		break;
		case AST_LESS:
		case AST_GREATER:
		case AST_LE:
		case AST_GE:
		case AST_EQ:
		case AST_DIF:
			if(node->son[0] != NULL && node->son[1] != NULL)
            {
				node->datatype = AST_DATATYPE_BOOL;
				if((node->son[0]->datatype != AST_DATATYPE_INT && node->son[0]->datatype != AST_DATATYPE_BYTE && node->son[0]->datatype != AST_DATATYPE_FLOAT) || 
					(node->son[1]->datatype != AST_DATATYPE_INT && node->son[1]->datatype != AST_DATATYPE_BYTE && node->son[1]->datatype != AST_DATATYPE_FLOAT))
                {
						fprintf(stderr,"SEMANTIC ERROR in line %d. Operators must be int, byte or float. \n",node->lineNumber);
						semanticError++;
						node->datatype = AST_DATATYPE_ERROR;
				}
			}	
		break;	
		case AST_AND:
		case AST_OR:
			if(node->son[0] != NULL && node->son[1] != NULL)
            {
				node->datatype = AST_DATATYPE_BOOL;
				if(node->son[0]->datatype != AST_DATATYPE_BOOL || node->son[1]->datatype != AST_DATATYPE_BOOL)
                {   
						fprintf(stderr,"SEMANTIC ERROR in line %d. Operators must be bool.\n",node->lineNumber);
						semanticError++;
						node->datatype = AST_DATATYPE_ERROR;
				}
			}
		break;
		case AST_NOT:
			if(node->son[0] != NULL)
            {
				node->datatype = AST_DATATYPE_BOOL;
				if(node->son[0]->datatype != AST_DATATYPE_BOOL)
                {
						fprintf(stderr,"SEMANTIC ERROR in line %d. Operators must be bool.\n",node->lineNumber);
						semanticError++;
						node->datatype = AST_DATATYPE_ERROR;
				}
			}
			break;
		default: 
        break;
	}

}

void checkSemantic(AST* node)
{
    fprintf(stderr, "\n"); 
	setAndCheckRedeclared(node);
	hashCheckUndeclared();
	checkOperands(node);
}

// ------------------------ FUNÇÕES AUXILIARES ------------------------

void setTypes(AST* node)
{
	if(node->son[0] != NULL)
    {
        if(node->son[0]->type == AST_INT)
        {
            node->son[0]->datatype = AST_DATATYPE_INT;
			node->symbol->datatype = SYMBOL_DATATYPE_INT;
			node->datatype = AST_DATATYPE_INT;
			
		} 
        else if(node->son[0]->type == AST_FLOAT)
        {
            node->son[0]->datatype = AST_DATATYPE_FLOAT;
			node->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
			node->datatype = AST_DATATYPE_FLOAT;
		}
		else if(node->son[0]->type == AST_BYTE)
        {
            node->son[0]->datatype = AST_DATATYPE_BYTE;
			node->symbol->datatype = SYMBOL_DATATYPE_BYTE;
			node->datatype = AST_DATATYPE_BYTE;	
		}  
	}
}

int numParamsFunc(AST* node)
{
	if(node == 0) 
        return 0;
	else
		return 1 + numParamsFunc(node->son[1]);
	
	return 0;
}

int checkVet(AST* node, int datatype)
{	
	if(node != NULL)
    {
		if((node->son[0]->symbol->datatype != datatype) || 
        (datatype == SYMBOL_DATATYPE_INT || datatype == SYMBOL_DATATYPE_BYTE) && 
        (node->son[0]->symbol->datatype != SYMBOL_DATATYPE_INT && node->son[0]->symbol->datatype != SYMBOL_DATATYPE_BYTE))
			return 0;
		if(node->son[1] != NULL)
			return checkVet(node->son[1], datatype);
	}
	return 1;
}

int getType(AST* node) 
{
    int op1, op2;
    
    switch(node->type) 
    {
        case AST_SYMBOL: 
        case AST_ARRAY:
        case AST_FUNCCALL:
            node->datatype = node->symbol->datatype;
        break;
        case AST_PARENTH:
            node->datatype = getType(node->son[0]);
        break;
        case AST_ADD:
        case AST_SUB:
        case AST_DIV:
        case AST_MULT:
                op1 = getType(node->son[0]);
                op2 = getType(node->son[1]);
                node->datatype = expressionTypes(op1,op2);
        break;
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_DIF:
        case AST_AND:
        case AST_OR: 
        case AST_GREATER:
        case AST_LESS: 
        case AST_NOT:
            node->datatype = SYMBOL_DATATYPE_BOOL;
        break;
    }

    return node->datatype;
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
        if (!checkParams(node))
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

            call_type = funccall_param->son[0]->datatype;

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

int validReturn(AST *nodeDec,AST *node)
{
    int dec_type=nodeDec->symbol->datatype;
    int return_type;
    if (node->type==AST_RETURN)
    {
        return_type=node->son[0]->datatype;
       
        if(dec_type!=return_type)
            if ((dec_type == SYMBOL_DATATYPE_BYTE && return_type == SYMBOL_DATATYPE_INT) || (dec_type == SYMBOL_DATATYPE_INT && return_type == SYMBOL_DATATYPE_BYTE))
                    return 1;
               
       		 else return 0;
        
        else return 1;
    }
    else
    {
        int number_sons = 0;

        for (number_sons = 0; number_sons < 4; number_sons++)
        {
            if (node->son[number_sons] != NULL)
            {
                int found;
                found = validReturn(nodeDec,node->son[number_sons]);
                if (found != 5)
                    return found;
            }
        }
    }

    return 5;

}

int checkParams(AST* node)
{
	int countParams = 0;

	int params = node->symbol->numparams;
	
	countParams = numParamsFunc(node->son[0]);

	if(countParams != params)
	{
		return 0;
	}

    return 1;	
}
