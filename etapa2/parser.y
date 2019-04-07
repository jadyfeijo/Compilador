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

%token KW_BYTE       256
%token KW_INT        257
%token KW_FLOAT      259
%token KW_IF         261
%token KW_THEN       262
%token KW_ELSE       263
%token KW_LOOP       264
%token KW_LEAP       265
%token KW_READ       266
%token KW_RETURN     267
%token KW_PRINT      268

%token OPERATOR_LE   270
%token OPERATOR_GE   271
%token OPERATOR_EQ   272
%token OPERATOR_DIF  273
%token OPERATOR_OR   274
%token OPERATOR_AND  275
%token OPERATOR_NOT  276

%token TK_IDENTIFIER 280
%token LIT_INTEGER   281
%token LIT_FLOAT     282
%token LIT_CHAR      285
%token LIT_STRING    286

%token TOKEN_ERROR 290

%left '<' '>' '='
%left '+' '-'
%left '*' '/'
%left OPERATOR_LE OPERATOR_GE
%left OPERATOR_EQ OPERATOR_DIF
%left OPERATOR_NOT OPERATOR_AND OPERATOR_OR

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
	| ;
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
	| ;
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
	| ;
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
	| ;
	;

array_init2:
	lit array_init2
	| ;
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
	| ;
	;

func_param2:
	',' func_param
	| ;
	;

%%

int yyerror (char *msg)
{
	fprintf(stderr, "Sintax error at line %d! \n", getLineNumber());
	exit(3);
}
	


