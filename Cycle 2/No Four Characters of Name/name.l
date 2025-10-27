%{
    #include <stdio.h>
%}

%%

.*navn.*    {printf("String rejected. Contains 'navn'\n");}
.*          {printf("String accpeted: %s\n", yytext);}

%%

int yywrap(){
    return 1;
}

int main(){
    yylex();
    return 0;
}