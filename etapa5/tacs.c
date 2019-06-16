//Eduarda Trindade 274709
//Jady Feijó 230210

#include <stdio.h>
#include <stdlib.h>
#include "tacs.h"

TAC* makeBinOp(TAC* result0, TAC* result1, int type);
TAC* makeIfThen(TAC* result0, TAC* result1);

TAC* tacCreate(int type, NODE *res, NODE *op1, NODE *op2)
{
    TAC *tac= (TAC*) calloc(1,sizeof(TAC));

    tac->type = type;
    tac->res = res;
    tac->op1 = op1;
    tac->op2 = op2;
    tac->prev = 0;
    tac->next = 0;

    return tac;
}

void tacPrintSingle(TAC *tac)
{
    if(tac == 0) return;

    fprintf(stderr, "TAC(");

    switch (tac->type)
    {
        case TAC_SYMBOL: fprintf(stderr,"TAC_SYMBOL");
            break;
        case TAC_ADD: fprintf(stderr,"TAC_ADD");
            break;
        case TAC_SUB: fprintf(stderr,"TAC_SUB");
            break;
        default: fprintf(stderr,"UNKNOWN");
            break;
    }

    if(tac->res == 0) fprintf(stderr, ",0");
    else fprintf(stderr,",%s",tac->res->text);
    if(tac->op1 == 0) fprintf(stderr, ",0");
    else fprintf(stderr,",%s",tac->op1->text);
    if(tac->op2 == 0) fprintf(stderr, ",0");
    else fprintf(stderr,",%s",tac->op2->text);
    fprintf(stderr,")\n");
}

void tacPrintBack(TAC *tac)
{
    if(tac)
    {
        tacPrintSingle(tac);
        tacPrintBack(tac->prev);
    }
}

void tacPrintForward(TAC *last)
{
    if(last)
    {
        tacPrintForward(last->prev);
        tacPrintSingle(last);
    }
}

void tacReverse(TAC *last)
{

}

TAC* tacJoin(TAC *l1, TAC *l2)
{
    TAC* tac;

    if (!l1) return l2;
    if (!l2) return l1;

    for (tac = l2; tac->prev; tac = tac->prev);
    tac->prev = l1;

    return l2;
}

TAC* generateCode(AST *node)
{
    int i;
    TAC* result[MAX_SONS];

    if(node == 0)
        return 0;

    for(i=0; i<MAX_SONS; i++)
        result[i] = generateCode(node->son[i]);

    switch (node->type)
    {
        case AST_SYMBOL:
            return tacCreate(TAC_SYMBOL, node->symbol,0,0);
            break;
        case AST_ADD:
            return tacCreate(TAC_ADD, makeTemp(),
                            result[0]?result[0]->res:0,
                            result[1]?result[1]->res:0);
            break;
        
        default: 
            //fprintf(stderr,"generateCode: UNKNOWN\n");
            break;
    }

    return tacJoin(tacJoin(tacJoin(result[0], result[1]), result[2]), result[3]);
}

TAC *makeBinOp(TAC* result0, TAC* result1, int type)
{
    return tacJoin(tacJoin(result0, result1),
					tacCreate(type, makeTemp(),
						    result0?result0->res:0,
						    result1?result1->res:0));
}

TAC* makeIfThen(TAC* result0, TAC* result1)
{

}