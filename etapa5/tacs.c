//Eduarda Trindade 274709
//Jady Feijó 230210

#include <stdio.h>
#include <stdlib.h>
#include "tacs.h"

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
    if(tac != 0) return;

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