//Eduarda Trindade 274709
//Jady Feijó 230210

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

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

void astDecompilation(char *output, AST *node)
{
    FILE *file = fopen(output, "a");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    int i;

    if(!node) return;
    
    switch (node->type)
    {
        case AST_SYMBOL:
            if(node->symbol)
                fprintf(file,"%s\n", node->symbol->text);
             else
                fprintf(file,"VAZIO \n");
            break;
        case AST_ADD:
            fprintf(file,"+ ");
            break;
        case AST_SUB:
            fprintf(file,"- ");
            break;
        case AST_MULT:
            fprintf(file,"* ");
            break;
        case AST_LESS:
            fprintf(file,"< ");
            break;
        case AST_GREATER:
            fprintf(file,"> ");
            break;
        case AST_LE:
            fprintf(file,"<= ");
            break;
        case AST_GE:
            fprintf(file,">= ");
            break;
        case AST_EQ:
            fprintf(file,"== ");
            break;
        case AST_DIF:
            fprintf(file,"!= ");
            break;
        case AST_OR:
            fprintf(file,"or ");
            break;
        case AST_AND:
            fprintf(file,"and ");
            break;
        case AST_NOT:
            fprintf(file,"not ");
            break;
        case AST_IFT:
            fprintf(file,"if ");
            break;
        case AST_IFTE:
            fprintf(file,"if ");
            break;
        case AST_LOOP:
            fprintf(file,"loop ");
            break;
        case AST_LEAP:
            fprintf(file,"leap ");
            break;
        case AST_PRINT:
            fprintf(file,"print ");
            break;
        case AST_READ:
            fprintf(file,"read ");
            break;
        case AST_RETURN:
            fprintf(file,"return ");
            break;
        case AST_LCMD:
            break;
        case AST_DECFUNC:
            if(node->symbol)
                fprintf(file,"%s\n", node->symbol->text);
             else
                fprintf(file,"VAZIO \n");
            break;
        case AST_VARDEC:
            if(node->symbol)
                fprintf(file,"%s\n", node->symbol->text);
             else
                fprintf(file,"VAZIO \n");
            break;
        case AST_ASSIGN:
            fprintf(file,"= ");
            break;
        case AST_ARRAY:
            break;
        case AST_BLOCK:
            fprintf(file,"{ ");
            break;
        case AST_PARENTH:
            fprintf(file,"( ");
            break;
        case AST_DECFUNC_VOID:
            if(node->symbol)
                fprintf(file,"%s\n", node->symbol->text);
             else
                fprintf(file,"VAZIO \n");
            break;
        case AST_VETDEC:
            if(node->symbol)
                fprintf(file,"%s\n", node->symbol->text);
             else
                fprintf(file,"VAZIO \n");
            break;
        case AST_DEC:
            break;
        case AST_DEC_PARAM:
            if(node->symbol)
                fprintf(file,"%s\n", node->symbol->text);
             else
                fprintf(file,"VAZIO \n");
            break;
        case AST_DEC_PARAM2:
            break;
        case AST_PRINT_PARAM:
            break;
        case AST_LITFLOAT:
            break;
        case AST_FLOAT:
            fprintf(file ,"float ");
            break;
        case AST_INT:
            fprintf(file, "int ");
            break;
        case AST_BYTE:
            fprintf(file, "byte ");
            break;
        case AST_ARRAY_INIT:
            break;
        case AST_ARRAY_INIT2:
            break;
        case AST_FUNCCALL:
            break;
        case AST_FUNC_PARAM:
            break;
        case AST_FUNC_PARAM2:
            break;
        case AST_VECSIZE:
            if(node->symbol)
                fprintf(file,"%s\n", node->symbol->text);
             else
                fprintf(file,"VAZIO \n");
            break;
        default:
            fprintf(file,"\nUNKNOWN\n");
        break;
    }

   for(i = 0; i < MAX_SONS; ++i)
        astDecompilation(output, node->son[i]);

    fclose(file);
}
