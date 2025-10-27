#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char keywords[32][10] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

bool isKeyword(char word[]){
    for(int i = 0; i < 32; i++){
        if(strcmp(word, keywords[i]) == 0)
            return true;
    }
    return false;
}

void analyzeTokens(FILE* f){
    char ch, word[100];
    while((ch = fgetc(f)) != EOF){
        if(isspace(ch))
            continue;
        if(isalpha(ch)){
            int i = 0;
            word[i++] = ch;
            while(!(ch = fgetc(f)) != EOF && isalnum(ch)){
                word[i++] = ch;
            }
            word[i] = '\0';
            ungetc(ch, f);
            if(isKeyword(word)){
                printf("KEYWORD: %s\n", word);
            }
            else{
                printf("IDENTIFIER: %s\n", word);
            }
        }
        else if(isdigit(ch)){
            int i = 0;
            word[i++] = ch;
            while((ch = fgetc(f)) != EOF && isdigit(ch)){
                word[i++] = ch;
            }
            word[i] = '\0';
            ungetc(ch, f);
            printf("NUMBER: %s\n", word);
        }
        else{
            printf("SYMBOL: %c\n", ch);
        }
    }
}

void main(){
    FILE* f = fopen("sample.c", "r");
    analyzeTokens(f);
}