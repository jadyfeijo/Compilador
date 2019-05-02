//Eduarda Trindade 274709
//Jady Feijó 230210

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern FILE *out;

AST *astCreate(int type, NODE *symbol, AST *s0, AST *s1, AST *s2, AST *s3)
{
    AST *newnode;

    newnode = (AST*)calloc(1,sizeof(AST));

    newnode->type = type;
    newnode->son[0] = s0;
    newnode->son[1] = s1;
    newnode->son[2] = s2;
    newnode->son[3] = s3;
    newnode->symbol = symbol;

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
            fprintf(stderr,"AST_SYMBOL,");
            break;
        case AST_ADD:
            fprintf(stderr,"AST_ADD,");
            break;
        case AST_SUB:
            fprintf(stderr,"AST_SUB,");
            break;
        case AST_MULT:
            fprintf(stderr,"AST_MULT,");
            break;
        case AST_DIV:
            fprintf(stderr,"AST_DIV,");
            break;
        case AST_LESS:
            fprintf(stderr,"AST_LESS,");
            break;
        case AST_GREATER:
            fprintf(stderr,"AST_GREATER,");
            break;
        case AST_LE:
            fprintf(stderr,"AST_LE,");
            break;
        case AST_GE:
            fprintf(stderr,"AST_GE,");
            break;
        case AST_EQ:
            fprintf(stderr,"AST_EQ,");
            break;
        case AST_DIF:
            fprintf(stderr,"AST_DIF,");
            break;
        case AST_OR:
            fprintf(stderr,"AST_OR,");
            break;
        case AST_AND:
            fprintf(stderr,"AST_AND,");
            break;
        case AST_NOT:
            fprintf(stderr,"AST_NOT,");
            break;
        case AST_IFT:
            fprintf(stderr,"AST_IFT,");
            break;
        case AST_IFTE:
            fprintf(stderr,"AST_IFTE,");
            break;
        case AST_LOOP:
            fprintf(stderr,"AST_LOOP,");
            break;
        case AST_LEAP:
            fprintf(stderr,"AST_LEAP,");
            break;
        case AST_PRINT:
            fprintf(stderr,"AST_PRINT,");
            break;
        case AST_READ:
            fprintf(stderr,"AST_READ,");
            break;
        case AST_RETURN:
            fprintf(stderr,"AST_RETURN,");
            break;
        case AST_LCMD:
            fprintf(stderr,"AST_LCMD,");
            break;
        case AST_DECFUNC:
            fprintf(stderr,"AST_DECFUNC,");
            break;
        case AST_VARDEC:
            fprintf(stderr,"AST_VARDEC,");
            break;
        case AST_ASSIGN:
            fprintf(stderr,"AST_ASSIGN,");
            break;
        case AST_ARRAY:
            fprintf(stderr,"AST_ARRAY,");
            break;
        case AST_BLOCK:
            fprintf(stderr,"AST_BLOCK,");
            break;
        case AST_PARENTH:
            fprintf(stderr,"AST_PARENTH,");
            break;
        case AST_DECFUNC_VOID:
            fprintf(stderr,"AST_DECFUNC_VOID,");
            break;
        case AST_VETDEC:
            fprintf(stderr,"AST_VETDEC,");
            break;
        case AST_DEC:
            fprintf(stderr,"AST_DEC,");
            break;
        case AST_DEC_PARAM:
            fprintf(stderr,"AST_DEC_PARAM,");
            break;
        case AST_DEC_PARAM2:
            fprintf(stderr,"AST_DEC_PARAM2,");
            break;
        case AST_PRINT_PARAM:
            fprintf(stderr,"AST_PRINT_PARAM,");
            break;
        case AST_LITFLOAT:
            fprintf(stderr,"AST_LITFLOAT,");
            break;
        case AST_FLOAT:
            fprintf(stderr,"AST_FLOAT,");
            break;
        case AST_INT:
            fprintf(stderr,"AST_INT,");
            break;
        case AST_BYTE:
            fprintf(stderr,"AST_BYTE,");
            break;
        case AST_ARRAY_INIT:
            fprintf(stderr,"AST_ARRAY_INIT,");
            break;
        case AST_ARRAY_INIT2:
            fprintf(stderr,"AST_ARRAY_INIT2,");
            break;
        case AST_FUNCCALL:
            fprintf(stderr,"AST_FUNCCALL,");
            break;
        case AST_FUNC_PARAM:
            fprintf(stderr,"AST_FUNC_PARAM,");
            break;
        case AST_FUNC_PARAM2:
            fprintf(stderr,"AST_FUNC_PARAM2,");
            break;
        case AST_VECSIZE:
            fprintf(stderr,"AST_VECSIZE,");
            break;
        default:
            fprintf(stderr,"AST_UNKNOWN,");
        break;
    }
    
    if(node->symbol)
        fprintf(stderr,"%s,\n", node->symbol->text);
    else
        fprintf(stderr,"'',\n");
    
    for(i = 0; i < MAX_SONS; ++i)
        astPrint(level+1, node->son[i]);
}

void astDecompilation(AST *node)
{
    int i;

    if(!node) return;
    
    switch (node->type)
    {
        case AST_SYMBOL:
            fprintf(out,"%s", node->symbol->text);
            break;
        case AST_ADD:
            astDecompilation(node->son[0]); fprintf(out," + "); astDecompilation(node->son[1]);
            break;
        case AST_SUB:
            astDecompilation(node->son[0]); fprintf(out," - "); astDecompilation(node->son[1]);
            break;
        case AST_MULT:
            astDecompilation(node->son[0]); fprintf(out," * "); astDecompilation(node->son[1]);
            break;
        case AST_DIV:
            astDecompilation(node->son[0]); fprintf(out," / "); astDecompilation(node->son[1]);
            break;
        case AST_LESS:
            astDecompilation(node->son[0]); fprintf(out," < "); astDecompilation(node->son[1]);
            break;
        case AST_GREATER:
            astDecompilation(node->son[0]); fprintf(out," > "); astDecompilation(node->son[1]);
            break;
        case AST_LE:
            astDecompilation(node->son[0]); fprintf(out," <= "); astDecompilation(node->son[1]);
            break;
        case AST_GE:
            astDecompilation(node->son[0]); fprintf(out," >= "); astDecompilation(node->son[1]);
            break;
        case AST_EQ:
            astDecompilation(node->son[0]); fprintf(out," == "); astDecompilation(node->son[1]);
            break;
        case AST_DIF:
            astDecompilation(node->son[0]); fprintf(out," != "); astDecompilation(node->son[1]);
            break;
        case AST_OR:
            astDecompilation(node->son[0]); fprintf(out," or "); astDecompilation(node->son[1]);
            break;
        case AST_AND:
            astDecompilation(node->son[0]); fprintf(out," and "); astDecompilation(node->son[1]);
            break;
        case AST_NOT:
             fprintf(out," not "); astDecompilation(node->son[0]);
            break;
        case AST_IFT:
            fprintf(out,"if("); astDecompilation(node->son[0]); fprintf(out,") then \n"); astDecompilation(node->son[1]);
            break;
        case AST_IFTE:
            fprintf(out,"if("); astDecompilation(node->son[0]); fprintf(out,") then "); astDecompilation(node->son[1]); fprintf(out,"else "); astDecompilation(node->son[1]);
            break;
        case AST_LOOP:
            fprintf(out,"loop("); astDecompilation(node->son[0]); fprintf(out,")"); astDecompilation(node->son[1]);
            break;
        case AST_LEAP:
            fprintf(out,"leap "); fprintf(out,"%s", node->symbol->text);
            break;
        case AST_PRINT:
            fprintf(out,"print "); astDecompilation(node->son[0]);
            break;
        case AST_READ:
            fprintf(out,"read "); fprintf(out,"%s", node->symbol->text);
            break;
        case AST_RETURN:
            fprintf(out,"return "); astDecompilation(node->son[0]);
            break;
        case AST_LCMD:
            if(node->son[1] != NULL)
            {
                astDecompilation(node->son[0]); fprintf(out,";\n"); astDecompilation(node->son[1]);
            }
            else
                astDecompilation(node->son[0]); fprintf(out,";\n");
            break;  
        case AST_DECFUNC:
            astDecompilation(node->son[0]); fprintf(out," "); fprintf(out,"%s", node->symbol->text); fprintf(out,"("); astDecompilation(node->son[1]); fprintf(out,")"); astDecompilation(node->son[2]); fprintf(out,";");
            break;
        case AST_VARDEC:
            astDecompilation(node->son[0]);  fprintf(out," "); fprintf(out,"%s", node->symbol->text); fprintf(out," = "); astDecompilation(node->son[1]); fprintf(out,";"); astDecompilation(node->son[2]);
            break;
        case AST_ASSIGN:
            fprintf(out,"%s", node->symbol->text); fprintf(out," = "); astDecompilation(node->son[0]);
            break;
        case AST_ARRAY:
                fprintf(out,"%s", node->symbol->text); 
                fprintf(out,": "); 
                astDecompilation(node->son[0]); 
                fprintf(out,"["); 	
                astDecompilation(node->son[1]); 
                fprintf(out,"]"); 	
				
				if(node->son[2]!=NULL)
					astDecompilation(node->son[2]);

				fprintf(out,";");
            break;
        case AST_BLOCK:
            fprintf(out,"\n{\n"); astDecompilation(node->son[0]); fprintf(out,"\n}");
            break;
        case AST_PARENTH:
            fprintf(out,"("); astDecompilation(node->son[0]); fprintf(out,")");
            break;
        case AST_DECFUNC_VOID:
            astDecompilation(node->son[0]); fprintf(out,"%s", node->symbol->text); fprintf(out, "()"); astDecompilation(node->son[1]);
            break;
        case AST_VETDEC:
            astDecompilation(node->son[0]); fprintf(out,"%s", node->symbol->text); fprintf(out,"["); astDecompilation(node->son[1]); fprintf(out,"]");  fprintf(out,": ");	
				
			if(node->son[2]!=NULL)
				astDecompilation(node->son[2]);

			fprintf(out,";");
            break;
        case AST_DEC:
            if(node->son[1] != NULL)
            {
                astDecompilation(node->son[0]); fprintf(out," \n"); astDecompilation(node->son[1]);
            }	
            else
                astDecompilation(node->son[0]);
            break;
        case AST_DEC_PARAM:
            fprintf(out,"%s\n", node->symbol->text);
            break;
        case AST_DEC_PARAM2:
            break;
        case AST_PRINT_PARAM:
            if(node->son[1] != NULL)
            {
        		astDecompilation(node->son[0]); fprintf(out,","); astDecompilation(node->son[1]);
            }
            else
           	 	astDecompilation(node->son[0]);
            break;
        case AST_LITFLOAT:
            break;
        case AST_FLOAT:
            fprintf(out ,"float ");
            break;
        case AST_INT:
            fprintf(out, "int ");
            break;
        case AST_BYTE:
            fprintf(out, "byte ");
            break;
        case AST_ARRAY_INIT:
            astDecompilation(node->son[0]);
            if(node->son[1] != NULL)
            {
                fprintf(out," "); astDecompilation(node->son[1]);
        	}
            break;
        case AST_ARRAY_INIT2:
            astDecompilation(node->son[0]);
            if(node->son[1] != NULL)
            {
                fprintf(out," "); astDecompilation(node->son[1]);
        	}
            break;
        case AST_FUNCCALL:
            fprintf(out,"%s", node->symbol->text); fprintf(out,"("); astDecompilation(node->son[0]); fprintf(out,")");
            break;
        case AST_FUNC_PARAM:
            break;
        case AST_FUNC_PARAM2:
            break;
        case AST_VECSIZE:
            fprintf(out,"%s", node->symbol->text);
            break;
        default:
            fprintf(out,"\nUNKNOWN\n");
        break;
    }

   //for(i = 0; i < MAX_SONS; ++i)
        //astDecompilation( node->son[i]);
    return;
}
