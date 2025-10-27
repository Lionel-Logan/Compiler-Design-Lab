%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(const char* s);
    int yylex();
%}

%token VALID INVALID

%%

stmt : INVALID
       {printf("Invalid Variable name\n");}
     | VALID
       {printf("Valid Variable name\n");}
     ;

%%

void yyerror(const char* s){
    printf("%s\n", s);
}

int main(){
    printf("Enter a variable name: ");
    yyparse();
    return 0;
}