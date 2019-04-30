//Eduarda Trindade 274709
//Jady Feijó 230210

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

AST *astCreate(int type, AST *s0, AST *s1, AST *s2, AST *s3)
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
        case AST_IFT:
            fprintf(stderr,"AST_IFT,\n");
            break;
        case AST_LCMD:
            fprintf(stderr,"AST_LCMD,\n");
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