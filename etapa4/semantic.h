#include <stdio.h>
#include "hash.h"
#include "ast.h"

void setAndCheckRedeclared(AST *node);
void checkOperands(AST *node);
int arithmeticOperation(int nodeType);