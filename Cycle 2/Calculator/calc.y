%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(const char* s);
    int yylex();
%}

%token NUMBER PLUS MINUS MULTIPLY DIVIDE MODULO LPAREN RPAREN
%left PLUS MINUS MODULO
%left MULTIPLY DIVIDE

%%

stmt :
     | stmt expr '\n'   {printf("%d\n", $2);}
     ;

expr : 
     | NUMBER
     | expr PLUS expr   {$$ = $1 + $3;}
     | expr MINUS expr  {$$ = $1 - $3;}
     | expr MULTIPLY expr   {$$ = $1 * $3;}
     | expr DIVIDE expr {$$ = $1 / $3;}
     | expr MODULO expr {$$ = $1 % $3;}
     | LPAREN expr RPAREN {$$ = $2;}
     ;

%%

void yyerror(const char* s){
    printf("%s", s);
}

int main(){
    printf("Enter expression: ");
    yyparse();
    return 0;
}