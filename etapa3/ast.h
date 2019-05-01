//Eduarda Trindade 274709
//Jady Feijó 230210

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
#define AST_FUNC 23
#define AST_DEC 24
#define AST_ASSIGN 25
#define AST_ARRAY 26
#define AST_BLOCK 27
#define AST_PARENTH 28

typedef struct ast_node
{
    int type;
    NODE *symbol;
    struct ast_node *son[MAX_SONS];
} AST;

AST *astCreate(int type, AST *s0, AST *s1, AST *s2, AST *s3);
void astPrint(int level, AST *node);
void astDecompilation(AST *node);