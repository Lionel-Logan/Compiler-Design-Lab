%{
    #include <stdio.h>
    #include <stdbool.h>
    #include <ctype.h>   
    #include <string.h> 

    void yyerror(const char* s);
    int yylex();
    char* process(char* input);
    extern char* yytext;
%}

%token INPUT

%%

stmt : INPUT
        {printf("%s\n", process(yytext));}
     ;
%%

char* process(char* input){
    char* content = strdup(input);
    int vowels = 0, consonants = 0, digits = 0;
    char vowelSet[5] = {'a', 'e', 'i', 'o', 'u'};
    for(int i = 0; content[i] != '\0'; i++){
        if(isalnum(content[i])){
            if(isdigit(content[i])){
                digits++;
            }
            else{
                bool isVowel = false;
                for(int j = 0; j < 5; j++){
                    if(content[i] == vowelSet[j]){
                        vowels++;
                        isVowel = true;
                        break;
                    }
                }
                if(!isVowel){
                    consonants++;
                }
            }
        }
    }

    char returnable[100];
    sprintf(returnable, "Consonants: %d\nVowels: %d\nDigits: %d", consonants, vowels, digits);
    return strdup(returnable);
}

void yyerror(const char* s){
    printf("%s\n", s);
}

int main(){
    printf("Enter string: ");
    yyparse();
    return 0;
}