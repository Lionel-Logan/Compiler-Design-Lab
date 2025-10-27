%{
    #include "y.tab.h"
%}

%%

[0-9]+      {yylval = atoi(yytext); return NUMBER;}
"+"         {return PLUS;}
"-"         {return MINUS;}
"*"         {return MULTIPLY;}
"/"         {return DIVIDE;}
"%"         {return MODULO;}
"("         {return LPAREN;}
")"         {return RPAREN;}
\n          {return '\n';}

%%

int yywrap(){
    return 1;
}