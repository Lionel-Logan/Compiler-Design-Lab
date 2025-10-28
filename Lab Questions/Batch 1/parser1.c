/*
    Write a C program to implement the shift reduce parser for the following:

    E -> 2E2
    E -> 3E3
    E -> 4
*/

#include <stdio.h>
#include <stdbool.h>

int top = -1, i = 0;
char stack[100];

void reduce(char* expr){
    bool isReduced = true;
    while(isReduced){
        isReduced = false;
        // E -> 4
        if(top >= 0 && stack[top] == '4'){
            stack[top] = 'E';
            stack[top + 1] = '\0';
            printf("%s\t%s\tREDUCE (E -> 4)\n", stack, expr + i);
            isReduced = true;
        }
        // E -> 3E3
        else if(top >= 2 && stack[top - 2] == '3' && stack[top - 1] == 'E' && stack[top] == '3'){
            stack[top - 2] = 'E';
            stack[--top] = '\0';
            top--;
            printf("%s\t%s\tREDUCE (E -> 3E3)\n", stack, expr + i);
            isReduced = true;
        }
        // E -> 2E2
        else if(top >= 2 && stack[top - 2] == '2' && stack[top - 1] == 'E' && stack[top] == '2'){
            stack[top - 2] = 'E';
            stack[--top] = '\0';
            top--;
            printf("%s\t%s\tREDUCE (E -> 2E2)\n", stack, expr + i);
            isReduced = true;
        }
    }
}

void shift(char* expr){
    while(expr[i] != '\0'){
        stack[++top] = expr[i];
        stack[top + 1] = '\0';
        printf("%s\t%s\tSHIFT\n", stack, expr + i);
        i++;
        reduce(expr);
    }
    printf("\n");
}

void main(){
    printf("=======SHIFT REDUCE PARSER=======\n\n");
    printf("Input Grammar: \n\n");
    printf("E -> 2E2\nE -> 3E3\nE -> 4\n\n");
    printf("Enter a valid expression to be parsed: ");
    char expr[100];
    scanf("%s", expr);

    printf("STACK\tINPUT\tACTION\n\n");
    shift(expr);

    if(top == 0 && expr[i] == '\0' && stack[top] == 'E'){
        printf("ACCEPTED\n");
    }
    else{
        printf("REJECTED\n");
    }
}