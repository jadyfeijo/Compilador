//Eduarda Trindade 274709
//Jady Feijó 230210

#include <stdio.h>
#include <stdlib.h>
#include "tacs.h"

TAC* makeBinOp(TAC* result[], int type);
TAC* makeIfThen(TAC* result0, TAC* result1); 
TAC* makeIfThenElse(TAC* result0, TAC* result1,TAC* result2);
TAC* makeFunc(TAC* symbol, TAC* params, TAC* code);
TAC* makeLoop(TAC* result0, TAC* result1);
TAC* makeLeap(TAC* result[], NODE* currentLabel);

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

    if(tac->type == TAC_SYMBOL) return;
    fprintf(stderr, "TAC(");

    switch (tac->type)
    {
        case TAC_ADD: fprintf(stderr,"TAC_ADD"); break;
        case TAC_SUB: fprintf(stderr,"TAC_SUB"); break;
        case TAC_MULT: fprintf(stderr,"TAC_MULT"); break;
        case TAC_DIV: fprintf(stderr,"TAC_DIV"); break;
        case TAC_COPY: fprintf(stderr,"TAC_COPY"); break;
        case TAC_IFZ: fprintf(stderr,"TAC_IFZ"); break;
        case TAC_LABEL: fprintf(stderr,"TAC_LABEL"); break;
        case TAC_JUMP: fprintf(stderr,"TAC_JUMP"); break;
        case TAC_LESS: fprintf(stderr,"TAC_LESS"); break;
        case TAC_GREATER: fprintf(stderr,"TAC_GREAT"); break;
        case TAC_LE: fprintf(stderr,"TAC_LE"); break;
        case TAC_GE: fprintf(stderr,"TAC_GE"); break;
        case TAC_EQ: fprintf(stderr,"TAC_EQ"); break;
        case TAC_DIF: fprintf(stderr,"TAC_DIF"); break;
        case TAC_AND: fprintf(stderr,"TAC_AND"); break;
        case TAC_OR: fprintf(stderr,"TAC_OR"); break;
        case TAC_NOT: fprintf(stderr,"TAC_NOT"); break;
        case TAC_RETURN: fprintf(stderr,"TAC_RETURN"); break;
        case TAC_PRINT: fprintf(stderr,"TAC_PRINT"); break;
        case TAC_READ: fprintf(stderr,"TAC_READ"); break;
        case TAC_BEGINFUN: fprintf(stderr,"TAC_BEGINFUN"); break;
        case TAC_FUNC_PARAM: fprintf(stderr,"TAC_FUNC_PARAM"); break;
        case TAC_FUNCCALL: fprintf(stderr,"TAC_FUNCCALL"); break;
        case TAC_ENDFUN: fprintf(stderr,"TAC_ENDFUN"); break;
        case TAC_ARRAY: fprintf(stderr,"TAC_ARRAY"); break;
        case TAC_VETDEC: fprintf(stderr,"TAC_VETDEC"); break;
        case TAC_PUSH: fprintf(stderr,"TAC_PUSH"); break;
        case TAC_POP: fprintf(stderr,"TAC_POP"); break;
        case TAC_VET_IND: fprintf(stderr,"TAC_VET_IND"); break;
        
        default: fprintf(stderr,"UNKNOWN TAC TYPE"); break;
    }

    if(tac->res == 0) 
        fprintf(stderr, ",0");
    else 
        fprintf(stderr,", %s",tac->res->text);

    if(tac->op1 == 0) 
        fprintf(stderr, ",0");
    else 
        fprintf(stderr,", %s",tac->op1->text);

    if(tac->op2 == 0) 
        fprintf(stderr, ",0");
    else 
        fprintf(stderr,", %s",tac->op2->text);

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

TAC* tacJoin(TAC *l1, TAC *l2)
{
    TAC* tac;

    if (!l1) return l2;
    if (!l2) return l1;

    for (tac = l2; tac->prev; tac = tac->prev);
    tac->prev = l1;

    return l2;
}

TAC* generateCode(AST *node, NODE *label)
{
    int i;
    TAC* result[MAX_SONS];

    if(node == 0)
        return 0;

    if(node->type == AST_LOOP)
		label = makeLabel();

    for(i=0; i<MAX_SONS; i++)
        result[i] = generateCode(node->son[i], label);

    switch (node->type)
    {
        case AST_SYMBOL: return tacCreate(TAC_SYMBOL, node->symbol,0,0);
        case AST_ADD: return makeBinOp(result, TAC_ADD);
        case AST_SUB: return makeBinOp(result, TAC_SUB);
        case AST_MULT: return makeBinOp(result, TAC_MULT);
        case AST_DIV: return makeBinOp(result, TAC_DIV);
        case AST_LESS: return makeBinOp(result, TAC_LESS);
	    case AST_GREATER: return makeBinOp(result, TAC_GREATER);
        case AST_LE: return makeBinOp(result, TAC_LE);
        case AST_GE: return makeBinOp(result, TAC_GE);
	    case AST_EQ: return makeBinOp(result, TAC_EQ);
	    case AST_DIF: return makeBinOp(result, TAC_DIF);
	    case AST_AND: return makeBinOp(result, TAC_AND);
	    case AST_OR: return makeBinOp(result, TAC_OR);
	    case AST_NOT: return makeBinOp(result, TAC_NOT);
   
        case AST_ASSIGN: return tacJoin(result[0], tacCreate(TAC_COPY, node->symbol, result[0]?result[0]->res:0, 0));
      	case AST_ASSIGNARRAY: return tacJoin(tacJoin(result[0],result[1]),tacCreate(TAC_COPY,node->symbol,result[1]?result[1]->res:0,result[0]?result[0]->res:0));
      	case AST_ARRAY: return tacJoin(result[0],tacCreate(TAC_VET_IND,makeTemp(),node->symbol,result[0]?result[0]->res:0));
        case AST_RETURN: return tacJoin(result[0],tacCreate(TAC_RETURN,result[0]->res,0,0));
        case AST_PRINT: return  tacJoin(tacJoin(result[0], tacCreate(TAC_PRINT, result[0]?result[0]->res:0, 0, 0)), result[1]);
        case AST_PRINT_PARAM: return result[0];
        case AST_READ: return tacCreate(TAC_READ,node->symbol,0,0);
        case AST_IFT: return makeIfThen(result[0],result[1]);
        case AST_IFTE: return makeIfThenElse(result[0],result[1],result[2]);
        case AST_LOOP: return makeLoop(result[0],result[1]);
        case AST_LEAP: return makeLeap(result,label);
        case AST_FUNCCALL: label = makeLabel(); return tacJoin(result[1],tacJoin(tacJoin(tacCreate(TAC_FUNCCALL,node->symbol,label,0),tacJoin(tacCreate(TAC_JUMP,node->symbol,0,0),tacCreate(TAC_LABEL,label,0,0))),tacCreate(TAC_PUSH,makeTemp(),0,0)));
        case AST_FUNC_PARAM: return tacJoin(tacJoin(result[0],tacCreate(TAC_POP,result[0]->res,0,0)),result[1]);
        case AST_FUNC_PARAM2: return result[0];
	    case AST_DEC: return tacJoin(result[0],result[1]);
        case AST_DECFUNC: return makeFunc(tacCreate(TAC_SYMBOL, node->symbol, 0, 0), result[1], result[2]);
        case AST_DECFUNC_VOID: return makeFunc(tacCreate(TAC_SYMBOL, node->symbol, 0, 0), result[1], result[2]);
        case AST_DEC_PARAM: return tacJoin(tacJoin(result[1],tacCreate(TAC_FUNC_PARAM,node->symbol,0,0)),result[2]);
        case AST_DEC_PARAM2: return result[0];

        default: 
            return tacJoin(tacJoin(tacJoin(result[0], result[1]), result[2]), result[3]);
    }
}

TAC *makeBinOp(TAC* result[], int type)
{
    NODE* op1;
	NODE* op2;

	if(result[0]) 
        op1 = result[0]->res; 
    else 
        op1 = 0;

	if(result[1]) 
        op2 = result[1]->res; 
    else 
        op2 = 0;

	return tacJoin(result[0],tacJoin(result[1],tacCreate(type,makeTemp(),op1,op2)));
}

TAC* makeIfThen(TAC* result0, TAC* result1)
{
	TAC* tacIf;
	NODE * label1;
	NODE * label2;

	label1= makeLabel();
	label2= makeLabel();

	  return tacIf = tacJoin(result0,tacJoin(tacJoin(tacCreate(TAC_IFZ,result0->res,label1,label2),tacCreate(TAC_LABEL,label1,0,0)),tacJoin(result1,tacCreate(TAC_LABEL,label2,0,0))));		
}

TAC* makeIfThenElse(TAC* result0, TAC* result1,TAC* result2)
{
	TAC* tacIfElse;
	NODE * label1;
	NODE * label2;

	label1= makeLabel();
	label2= makeLabel();

	   return tacIfElse = tacJoin(result0,tacJoin(tacJoin(tacCreate(TAC_IFZ,result0->res,label1,label2),tacCreate(TAC_LABEL,label1,0,0)),tacJoin(result1,tacJoin(tacCreate(TAC_LABEL,label2,0,0),result2))));	
}

TAC* makeFunc(TAC* symbol, TAC* params, TAC* code)
{
	return tacJoin(tacJoin(tacJoin( tacCreate(TAC_BEGINFUN, symbol->res, 0, 0), params) , code ), tacCreate(TAC_ENDFUN, symbol->res, 0, 0));
}

TAC* makeLoop(TAC* result0, TAC* result1)
{
    TAC* tacWhile;
	NODE * label1;
	NODE * label2;
	NODE * label3;

	label1 = makeLabel();
	label2 = makeLabel();
	label3 = makeLabel();

 	return tacWhile = tacJoin(tacCreate(TAC_LABEL,label3,0,0),tacJoin(result0,tacJoin(tacCreate(TAC_IFZ,result0->res,label1,label2),tacJoin(tacCreate(TAC_LABEL,label1,0,0),tacJoin(result1,tacJoin(tacCreate(TAC_JUMP,label3,0,0),tacCreate(TAC_LABEL, label2,0,0)))))));
}

TAC* makeLeap(TAC* result[], NODE* currentLabel)
{
    TAC *jump = tacCreate(TAC_JUMP,currentLabel,0,0);

    return jump;
}
