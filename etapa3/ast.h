//Eduarda Trindade 274709
//Jady Feijó 230210

#include <stdio.h>

#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 3
#define AST_IFT 4
#define AST_LCMD 5

typedef struct ast_node
{
    int type;
    NODE *symbol;
    struct ast_node *son[MAX_SONS];
} AST;

AST *astCreate(int type, AST *s0, AST *s1, AST *s2, AST *s3);
void astPrint(int level, AST *node);