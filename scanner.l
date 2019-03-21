%{ 
    //Eduarda Trindade 274709
    //Jady Feijó 230210

    #include <stdio.h>
    #include <stdlib.h>
    #include "tokens.h"
    //#include "hash.c"
	
	int isRunning = 1;
	int line = 1;
%}

%x COMMENT

%%

"byte"                        { return KW_BYTE; }
"int"                         { return KW_INT; }
"float"                       { return KW_FLOAT; }
"if"                          { return KW_IF; }
"then"                        { return KW_THEN; }
"else"                        { return KW_ELSE; }
"loop"                        { return KW_LOOP; }
"leap"                        { return KW_LEAP; }
"read"                        { return KW_READ; }
"return"                      { return KW_RETURN ; }
"print"                       { return KW_PRINT; }
"or"                          { return OPERATOR_OR ; }
"and"                         { return OPERATOR_AND; }
"not"                         { return OPERATOR_NOT; }

[a-z_0-9]+                    { return TK_IDENTIFIER; } // conferir, acho que isso está errado

[0-9]+"."[0-9]+				  { return LIT_FLOAT; } //Nao sei se essas do LIT estão certas, não testei
"'"[A-Za-z.]"'"				  { return LIT_CHAR; } 
"\"" [A-Za-z.]+"\""			  { return LIT_STRING; }

[-+*/=(){}<>;,:&$#]           { return (int)yytext[0]; }
"["                           { return (int)yytext[0]; }
"]"                           { return (int)yytext[0]; }

"<="                          { return OPERATOR_LE; }
">="                          { return OPERATOR_GE; }
"=="                          { return OPERATOR_EQ; }
"!="                          { return OPERATOR_DIF; }

[ \t]
"\n"						  { ++line; }

"ZZ".*
"XXX"					      { BEGIN(COMMENT); }
.				              { return TOKEN_ERROR; }

<COMMENT>"XXX"				  { BEGIN(INITIAL); }
<COMMENT>.					
<COMMENT>"\n"				  { ++line; }

%%

int yywrap(void) 
{
    isRunning = 0;
    return 1;
} 