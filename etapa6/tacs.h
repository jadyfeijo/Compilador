//Eduarda Trindade 274709
//Jady Feijó 230210

#ifndef TACS_HEADER
#define TACS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MULT 4
#define TAC_DIV 5
#define TAC_COPY 6
#define TAC_IFZ 7
#define TAC_LABEL 8
#define TAC_JUMP 9
#define TAC_LESS 10
#define TAC_GREATER 11
#define TAC_LE 12
#define TAC_GE 13
#define TAC_EQ 14
#define TAC_DIF 15
#define TAC_AND 16
#define TAC_OR 17
#define TAC_NOT 18
#define TAC_RETURN 19
#define TAC_PRINT 20
#define TAC_READ 21
#define TAC_BEGINFUN 22
#define TAC_ENDFUN 23
#define TAC_ARRAY 24
#define TAC_VETDEC 25
#define TAC_FUNCCALL 26
#define TAC_PARAM 27
#define TAC_FUNC_PARAM 28
#define TAC_PUSH 29
#define TAC_POP 30
#define TAC_VET_IND 31
#define TAC_ASSIGNARRAY 32

typedef struct tac_node
{
    int type;
    NODE *res;
    NODE *op1;
    NODE *op2;
    struct tac_node *prev;
    struct tac_node *next;
}TAC;

TAC* tacCreate(int type, NODE *res, NODE *op1, NODE *op2);
void tacPrintSingle(TAC *tac);
void tacPrintBack(TAC *tac);
void tacPrintForward(TAC *last);
TAC* tacJoin(TAC *l1, TAC *l2);
TAC* tacReverse(TAC *last);

TAC* generateCode(AST *node,NODE *label);

#endif
