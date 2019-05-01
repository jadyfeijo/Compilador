//Eduarda Trindade 274709
//Jady Feijó 230210

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

AST *astCreate(int type, NODE *symbol,AST *s0, AST *s1, AST *s2, AST *s3)
{
    AST *newnode;

    newnode = (AST*)calloc(1,sizeof(AST));

    newnode->type = type;
    newnode->son[0] = s0;
    newnode->son[1] = s1;
    newnode->son[2] = s2;
    newnode->son[3] = s3;

    return newnode;
}

void astPrint(int level, AST *node)
{
    int i;

    if(!node) return;

    for(i=0;i<level;i++)
	fprintf(stderr," ");
    
    fprintf(stderr,"AST(");

    switch (node->type)
    {
         case AST_SYMBOL:
            fprintf(stderr,"AST_SYMBOL,\n");
            break;
        case AST_ADD:
            fprintf(stderr,"AST_ADD,\n");
            break;
        case AST_SUB:
            fprintf(stderr,"AST_SUB,\n");
            break;
        case AST_MULT:
            fprintf(stderr,"AST_MULT,\n");
            break;
        case AST_LESS:
            fprintf(stderr,"AST_LESS,\n");
            break;
        case AST_GREATER:
            fprintf(stderr,"AST_GREATER,\n");
            break;
        case AST_LE:
            fprintf(stderr,"AST_LE,\n");
            break;
        case AST_GE:
            fprintf(stderr,"AST_GE,\n");
            break;
        case AST_EQ:
            fprintf(stderr,"AST_EQ,\n");
            break;
        case AST_DIF:
            fprintf(stderr,"AST_DIF,\n");
            break;
        case AST_OR:
            fprintf(stderr,"AST_OR,\n");
            break;
        case AST_AND:
            fprintf(stderr,"AST_AND,\n");
            break;
        case AST_NOT:
            fprintf(stderr,"AST_NOT,\n");
            break;
        case AST_IFT:
            fprintf(stderr,"AST_IFT,\n");
            break;
        case AST_IFTE:
            fprintf(stderr,"AST_IFTE,\n");
            break;
        case AST_LOOP:
            fprintf(stderr,"AST_LOOP,\n");
            break;
        case AST_LEAP:
            fprintf(stderr,"AST_LEAP,\n");
            break;
        case AST_PRINT:
            fprintf(stderr,"AST_PRINT,\n");
            break;
        case AST_READ:
            fprintf(stderr,"AST_READ,\n");
            break;
        case AST_RETURN:
            fprintf(stderr,"AST_RETURN,\n");
            break;
        case AST_LCMD:
            fprintf(stderr,"AST_LCMD,\n");
            break;
        case AST_DECFUNC:
            fprintf(stderr,"AST_DECFUNC,\n");
            break;
        case AST_VARDEC:
            fprintf(stderr,"AST_VARDEC,\n");
            break;
        case AST_ASSIGN:
            fprintf(stderr,"AST_ASSIGN,\n");
            break;
        case AST_ARRAY:
            fprintf(stderr,"AST_ARRAY,\n");
            break;
        case AST_BLOCK:
            fprintf(stderr,"AST_BLOCK,\n");
            break;
        case AST_PARENTH:
            fprintf(stderr,"AST_PARENTH,\n");
            break;
	case AST_DECFUNC_VOID:
	    fprintf(stderr,"AST_DECFUNC_VOID,\n");
	    break;
	case AST_VETDEC:
	    fprintf(stderr,"AST_VETDEC,\n");
	    break;
	case AST_DEC:
	    fprintf(stderr,"AST_DEC,\n");
	    break;
	case AST_DEC_PARAM:
	    fprintf(stderr,"AST_DEC_PARAM,\n");
	    break;
	case AST_DEC_PARAM2:
	    fprintf(stderr,"AST_DEC_PARAM2,\n");
	    break;
	case AST_PRINT_PARAM:
	    fprintf(stderr,"AST_PRINT_PARAM,\n");
	    break;
	case AST_LITFLOAT:
	    fprintf(stderr,"AST_LITFLOAT,\n");
	    break;
	case AST_FLOAT:
	    fprintf(stderr,"AST_FLOAT,\n");
	    break;
	case AST_INT:
	    fprintf(stderr,"AST_INT,\n");
	    break;
	case AST_BYTE:
	    fprintf(stderr,"AST_BYTE,\n");
	    break;
	case AST_ARRAY_INIT:
            fprintf(stderr,"AST_ARRAY_INIT,\n");
            break;
	case AST_ARRAY_INIT2:
            fprintf(stderr,"AST_ARRAY_INIT2,\n");
            break;
	case AST_FUNCCALL:
            fprintf(stderr,"AST_FUNCCALL,\n");
            break;
	case AST_FUNC_PARAM:
            fprintf(stderr,"AST_FUNC_PARAM,\n");
            break;
	case AST_FUNC_PARAM2:
            fprintf(stderr,"AST_FUNC_PARAM2,\n");
            break;

	
        default:
            fprintf(stderr,"AST_UNKNOWN,\n");
break;
    }

    if(node->symbol)
        fprintf(stderr,"%s,\n", node->symbol->text);
    else
        fprintf(stderr,"'',\n");

    for(i = 0; i < MAX_SONS; ++i)
        astPrint(level+1, node->son[i]);
    
}//Eduarda Trindade 274709
//Jady Feijó 230210

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

AST *astCreate(int type, NODE *symbol,AST *s0, AST *s1, AST *s2, AST *s3)
{
    AST *newnode;

    newnode = (AST*)calloc(1,sizeof(AST));

    newnode->type = type;
    newnode->son[0] = s0;
    newnode->son[1] = s1;
    newnode->son[2] = s2;
    newnode->son[3] = s3;

    return newnode;
}

void astPrint(int level, AST *node)
{
    int i;

    if(!node) return;

    for(i=0;i<level;i++)
	fprintf(stderr," ");
    
    fprintf(stderr,"AST(");

    switch (node->type)
    {
         case AST_SYMBOL:
            fprintf(stderr,"AST_SYMBOL,\n");
            break;
        case AST_ADD:
            fprintf(stderr,"AST_ADD,\n");
            break;
        case AST_SUB:
            fprintf(stderr,"AST_SUB,\n");
            break;
        case AST_MULT:
            fprintf(stderr,"AST_MULT,\n");
            break;
        case AST_LESS:
            fprintf(stderr,"AST_LESS,\n");
            break;
        case AST_GREATER:
            fprintf(stderr,"AST_GREATER,\n");
            break;
        case AST_LE:
            fprintf(stderr,"AST_LE,\n");
            break;
        case AST_GE:
            fprintf(stderr,"AST_GE,\n");
            break;
        case AST_EQ:
            fprintf(stderr,"AST_EQ,\n");
            break;
        case AST_DIF:
            fprintf(stderr,"AST_DIF,\n");
            break;
        case AST_OR:
            fprintf(stderr,"AST_OR,\n");
            break;
        case AST_AND:
            fprintf(stderr,"AST_AND,\n");
            break;
        case AST_NOT:
            fprintf(stderr,"AST_NOT,\n");
            break;
        case AST_IFT:
            fprintf(stderr,"AST_IFT,\n");
            break;
        case AST_IFTE:
            fprintf(stderr,"AST_IFTE,\n");
            break;
        case AST_LOOP:
            fprintf(stderr,"AST_LOOP,\n");
            break;
        case AST_LEAP:
            fprintf(stderr,"AST_LEAP,\n");
            break;
        case AST_PRINT:
            fprintf(stderr,"AST_PRINT,\n");
            break;
        case AST_READ:
            fprintf(stderr,"AST_READ,\n");
            break;
        case AST_RETURN:
            fprintf(stderr,"AST_RETURN,\n");
            break;
        case AST_LCMD:
            fprintf(stderr,"AST_LCMD,\n");
            break;
        case AST_DECFUNC:
            fprintf(stderr,"AST_DECFUNC,\n");
            break;
        case AST_VARDEC:
            fprintf(stderr,"AST_VARDEC,\n");
            break;
        case AST_ASSIGN:
            fprintf(stderr,"AST_ASSIGN,\n");
            break;
        case AST_ARRAY:
            fprintf(stderr,"AST_ARRAY,\n");
            break;
        case AST_BLOCK:
            fprintf(stderr,"AST_BLOCK,\n");
            break;
        case AST_PARENTH:
            fprintf(stderr,"AST_PARENTH,\n");
            break;
	case AST_DECFUNC_VOID:
	    fprintf(stderr,"AST_DECFUNC_VOID,\n");
	    break;
	case AST_VETDEC:
	    fprintf(stderr,"AST_VETDEC,\n");
	    break;
	case AST_DEC:
	    fprintf(stderr,"AST_DEC,\n");
	    break;
	case AST_DEC_PARAM:
	    fprintf(stderr,"AST_DEC_PARAM,\n");
	    break;
	case AST_DEC_PARAM2:
	    fprintf(stderr,"AST_DEC_PARAM2,\n");
	    break;
	case AST_PRINT_PARAM:
	    fprintf(stderr,"AST_PRINT_PARAM,\n");
	    break;
	case AST_LITFLOAT:
	    fprintf(stderr,"AST_LITFLOAT,\n");
	    break;
	case AST_FLOAT:
	    fprintf(stderr,"AST_FLOAT,\n");
	    break;
	case AST_INT:
	    fprintf(stderr,"AST_INT,\n");
	    break;
	case AST_BYTE:
	    fprintf(stderr,"AST_BYTE,\n");
	    break;
	case AST_ARRAY_INIT:
            fprintf(stderr,"AST_ARRAY_INIT,\n");
            break;
	case AST_ARRAY_INIT2:
            fprintf(stderr,"AST_ARRAY_INIT2,\n");
            break;
	case AST_FUNCCALL:
            fprintf(stderr,"AST_FUNCCALL,\n");
            break;
	case AST_FUNC_PARAM:
            fprintf(stderr,"AST_FUNC_PARAM,\n");
            break;
	case AST_FUNC_PARAM2:
            fprintf(stderr,"AST_FUNC_PARAM2,\n");
            break;

	
        default:
            fprintf(stderr,"AST_UNKNOWN,\n");
break;
    }

    if(node->symbol)
        fprintf(stderr,"%s,\n", node->symbol->text);
    else
        fprintf(stderr,"'',\n");

    for(i = 0; i < MAX_SONS; ++i)
        astPrint(level+1, node->son[i]);
    
}
