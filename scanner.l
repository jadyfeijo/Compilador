%{ 
    //Eduarda Trindade 274709
    //Jady Feijó 230210

    #include <stdio.h>
    #include <stdlib.h>
    #include "tokens.h"
    #include "hash.h"


	
    int isRunning = 1;
    int line=1;

    int getLineNumber(void)
{

    return line;
}

    void initMe()
{
    hashInit();
}
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

[a-z_0-9]+                    { hashInsert(0,yytext); return TK_IDENTIFIER; } 
[A-IO]+                       { hashInsert(0,yytext); return LIT_INTEGER; }

[0-9]+"."[0-9]+		      { return LIT_FLOAT; } 
"'"."'"		              { hashInsert(0,yytext); return LIT_CHAR; } 
"\"".+"\""  		      { hashInsert(0,yytext); return LIT_STRING; }

[-+*/=(){}<>;,:&$#]           { fprintf(stdout," <%c> ",(int)yytext[0]); }
"["                           { fprintf(stdout," <%c> ",(int)yytext[0]); }
"]"                           { fprintf(stdout," <%c> ",(int)yytext[0]); }

"<="                          { return OPERATOR_LE; }
">="                          { return OPERATOR_GE; }
"=="                          { return OPERATOR_EQ; }
"!="                          { return OPERATOR_DIF; }

[ \t]
"\n"			      { ++line; }

"ZZ".* 
"XXX"			      { BEGIN(COMMENT); }
.		              { return TOKEN_ERROR; }

<COMMENT>"XXX"		      { BEGIN(INITIAL); }
<COMMENT>.					
<COMMENT>"\n"	   	      { ++line; }

%%

//#include "main.c"

int yywrap(void) 
{
    isRunning = 0;
    return 1;
} 
