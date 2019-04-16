%{
	//Eduarda Trindade 274709
    //Jady Feijó 230210

	#include <stdio.h>
	#include <stdlib.h>
	#include "hash.h"

	int yyerror (char *msg);
	int yylex(void);
	int getLineNumber(void);
%}

%token KW_BYTE
%token KW_INT
%token KW_FLOAT
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_LOOP
%token KW_LEAP
%token KW_READ
%token KW_RETURN
%token KW_PRINT

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token OPERATOR_OR
%token OPERATOR_AND
%token OPERATOR_NOT

%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_FLOAT
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%left '<' '>' '='
%left '-' '+'
%left '/' '*'
%left OPERATOR_LE OPERATOR_GE
%left OPERATOR_DIF OPERATOR_EQ
%left OPERATOR_OR OPERATOR_AND OPERATOR_NOT  

%%

program: declist
	;

declist: dec declist
	|
	;

dec: 
	type TK_IDENTIFIER '=' lit ';'
	| type TK_IDENTIFIER '['LIT_INTEGER']' array_init ';'
	| type TK_IDENTIFIER '('')'cmd
	| type TK_IDENTIFIER '('dec_param')'cmd
	;

dec_param:
	type TK_IDENTIFIER dec_param2
	;

dec_param2:
	',' dec_param
	|
	;

cmd:
	TK_IDENTIFIER '=' exp 
	| TK_IDENTIFIER '[' exp ']' '=' exp
	| KW_RETURN exp 
	| KW_READ TK_IDENTIFIER
	| KW_PRINT print_list
	| block 
	| ctrl_fluxo
	| ';'
	;

block:
	'{' cmd_list '}' ';'
	;

cmd_list: 
	cmd cmd_list
	|
	;

ctrl_fluxo:
	KW_IF '(' exp ')' KW_THEN cmd
	| KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd
	| KW_IF '(' exp ')' KW_THEN KW_ELSE cmd
	| KW_LOOP '(' exp ')' cmd
	| KW_LEAP
	;
	
print_list:
	LIT_STRING print_list2
	| exp print_list2
	;
	
print_list2:
	',' print_list
	|
	;

lit:
	LIT_INTEGER
	| LIT_FLOAT
	| LIT_CHAR
	;

type:
	KW_INT
	| KW_FLOAT
	| KW_BYTE
	;

array_init:
	':' lit array_init2
	|
	;

array_init2:
	lit array_init2
	|
	;

exp:
	TK_IDENTIFIER
	| TK_IDENTIFIER '[' exp ']'
	| TK_IDENTIFIER '(' func_param ')'
	| '(' exp ')'
	| lit
	| exp '+' exp
	| exp '-' exp
	| exp '*' exp
	| exp '/' exp
	| exp OPERATOR_LE exp
	| exp OPERATOR_GE exp
	| exp OPERATOR_EQ exp
	| exp OPERATOR_DIF exp
	| exp OPERATOR_OR exp
	| exp OPERATOR_AND exp
	| exp OPERATOR_NOT exp
	| exp '>' exp
	| exp '<' exp
	;

func_param:
	exp func_param2
	|
	;

func_param2:
	',' func_param
	|
	;

%%

int yyerror (char *msg)
{
	fprintf(stderr, "Sintax error at line %d! \n", getLineNumber());
	exit(3);
}
	


