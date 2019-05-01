//Eduarda Trindade 274709
//Jady Feijó 230210

#ifndef AST_HEADER
#define AST_HEADER
#include <stdio.h>
#include "hash.h"

#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 3
#define AST_MULT 4
#define AST_DIV 5
#define AST_LESS 6
#define AST_GREATER 7
#define AST_LE 8
#define AST_GE 9
#define AST_EQ 10
#define AST_DIF 11
#define AST_OR 12
#define AST_AND 13
#define AST_NOT 14
#define AST_IFT 15
#define AST_IFTE 16
#define AST_LOOP 17
#define AST_LEAP 18
#define AST_PRINT 19
#define AST_READ 20
#define AST_RETURN 21
#define AST_LCMD 22
#define AST_DECFUNC 23
#define AST_VARDEC 24
#define AST_ASSIGN 25
#define AST_ARRAY 26
#define AST_BLOCK 27
#define AST_PARENTH 28
#define AST_DECFUNC_VOID 29
#define AST_VETDEC 30
#define AST_DEC 31
#define AST_DEC_PARAM 32
#define AST_DEC_PARAM2 33
#define AST_PRINT_PARAM 34
#define AST_LITFLOAT 35
#define AST_INT 36
#define AST_FLOAT 37
#define AST_BYTE 38
#define AST_ARRAY_INIT 39
#define AST_ARRAY_INIT2 40
#define AST_FUNCCALL 41
#define AST_FUNC_PARAM 42
#define AST_FUNC_PARAM2 43




typedef struct ast_node
{
    int type;
    NODE *symbol;
    struct ast_node *son[MAX_SONS];
} AST;

AST *astCreate(int type, NODE *symbol,AST *s0, AST *s1, AST *s2, AST *s3);
void astPrint(int level, AST *node);

#endif
