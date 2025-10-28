%{
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*      {char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default", "do","double", "else", "enum", "extern", "float", "for", "goto", "if","int", "long", "register", "return", "short", "signed", "sizeof", "static","struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
bool flag = false;
for(int i = 0; i < 32; i++){
    if(strcmp(yytext, keywords[i]) == 0){
        printf("Invalid Variable\n"); 
        flag = true;
        break;
    }
}
if(!flag){
    printf("Valid Variable\n");
}}
[0-9a-zA-Z_][a-zA-Z0-9_]*   {printf("Invalid Variable\n");}

%%

int yywrap(){
    return 1;
}

int main(){
    yylex();
    return 0;
}