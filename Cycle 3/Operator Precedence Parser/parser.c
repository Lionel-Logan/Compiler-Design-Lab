#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char table[100][100];
char terminals[100];
char stack[100];

int top = -1;

void formulateTable(FILE* f, int n){
    char content[100];
    for(int i = 0; i < n; i++){
        if(fscanf(f, "%s", content) != 1){
            break;
        }
        for(int j = 0; j < n; j++){
            table[i][j] = content[j];
        }
    }
}

char getTerminalFromStack(){
    int i = top;
    while(i >= 0){
        if(stack[i] != '<' && stack[i] != '>' && stack[i] != '='){
            return stack[i];
        }
        i--;
    }
    return '$';
}

int getIndex(char ch){
    for(int i = 0; terminals[i] != '\0'; i++){
        if(terminals[i] == ch){
            return i;
        }
    }
    return -1;
}

void parse(char* input){
    stack[++top] = '$';
    strcat(input, "$");
    int i = 0;
    while(true){
        char a = getTerminalFromStack();
        char b = input[i];

        int indexA = getIndex(a);
        int indexB = getIndex(b);

        if(a == '$' && b == '$'){
            printf("ACCEPTED\n");
            break;
        }

        if(table[indexA][indexB] == '<' || table[indexA][indexB] == '='){
            stack[++top] = table[indexA][indexB];
            stack[++top] = input[i];
            stack[top + 1] = '\0';
            i++;
            printf("%s\t%s\tSHIFT\n", stack, input + i);
        }
        else if(table[indexA][indexB] == '>'){
            while(top > 0 && stack[top] != '<'){
                top--;
            }
            if(top > 0){
                top--;
            }
            stack[top + 1] = '\0';
            printf("%s\t%s\tREDUCE\n", stack, input + i);
        }
    }
}

void main(){
    FILE* f = fopen("table.txt", "r");
    printf("Enter the terminals (without spaces, including $): ");
    scanf("%s", terminals);
    formulateTable(f, strlen(terminals));

    printf("Enter input string: ");
    char input[100];
    scanf("%s", input);

    printf("\nSTACK\tINPUT\tACTION\n\n");
    parse(input);
}