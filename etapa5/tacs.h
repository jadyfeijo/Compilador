//Eduarda Trindade 274709
//Jady Feijó 230210

#ifdef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3

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

#endif