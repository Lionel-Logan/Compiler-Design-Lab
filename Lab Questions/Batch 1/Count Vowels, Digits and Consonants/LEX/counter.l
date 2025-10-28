%{
    #include <stdio.h>    
    #include <ctype.h>
    #include <stdbool.h>
%}

%%

.*      {
    char* content = strdup(yytext);
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
    printf("Consonants: %d\nVowels: %d\nDigits: %d\n", consonants, vowels, digits);
}

%%

int yywrap(){
    return 1;
}

int main(){
    yylex();
    return 0;
}