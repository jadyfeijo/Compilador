%{ 
    //Eduarda Trindade 274709
    //Jady Feijó 230210

    #include <stdio.h>
    #include <stdlib.h>
    #include "hash.c"
    #include "ast.h"
    #include "y.tab.h"

    int IsRunning = 1;
    int Line = 1;
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

[a-z_0-9]+                    { if( yytext[-1]!='"')
                                { yylval.symbol = hashInsert(TK_IDENTIFIER,yytext); 
                                  return TK_IDENTIFIER;
                                }
                              } 
                                  
[A-IO]+                       { yylval.symbol = hashInsert(LIT_INTEGER,yytext); return LIT_INTEGER; }

[A-IO]+"."[A-IO]+		      { yylval.symbol = hashInsert(LIT_FLOAT,yytext); return LIT_FLOAT; }
'(\\.|[^'\n])*\'		      { if (yyleng==3)
                                { yylval.symbol = hashInsert(LIT_CHAR,yytext);
                                   return LIT_CHAR;
                                }
                                  else return TOKEN_ERROR;
                              } 
                
\"(\\.|[^\"\n])*\"   		  { yylval.symbol = hashInsert(LIT_STRING,yytext); return LIT_STRING;}

[-+*/=(){}<>;,:&$#]           { return (int)yytext[0]; }
"["                           { return (int)yytext[0]; }
"]"                           { return (int)yytext[0]; }

"<="                          { return OPERATOR_LE; }
">="                          { return OPERATOR_GE; }
"=="                          { return OPERATOR_EQ; }
"!="                          { return OPERATOR_DIF; }

[ \t]
"\n"			              { ++Line; }

"ZZ".*  
"XXX"			              { BEGIN(COMMENT); }
.		                      { return TOKEN_ERROR; }

<COMMENT>"XXX"		          { BEGIN(INITIAL); }
<COMMENT>.					
<COMMENT>"\n"	   	          { ++Line; }

%%
int getLineNumber(void)
{   
    return Line;
}

void initMe(void)
{
    hashInit();
}

int isRunning(void)
{
    return IsRunning;
}
    
int yywrap(void) 
{
    IsRunning = 0;
    return 1;
} 
