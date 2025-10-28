/*
    Write a C program to implement the shift reduce parser for the following:

    S -> S + S
    S -> S * S
    S -> a
*/

#include <stdio.h>
#include <stdbool.h>

int top = -1, i = 0;
char stack[100];

void reduce(char* expr){
    bool isReduced = true;
    while(isReduced){
        isReduced = false;
        //S -> a
        if(top >= 0 && stack[top] == 'a'){
            stack[top] = 'S';
            stack[top + 1] = '\0';
            printf("%s\t%s\tREDUCE (S -> a)\n", stack, expr + i);
            isReduced = true;
        }
        //S -> S * S
        else if(top >= 2 && stack[top - 2] == 'S' && stack[top - 1] == '*' && stack[top] == 'S'){
            stack[top - 2] = 'S';
            stack[--top] = '\0';
            top--;
            printf("%s\t%s\tREDUCE (S -> S * S)\n", stack, expr + i);
            isReduced = true;
        }
        //S -> S + S
        else if(top >= 2 && stack[top - 2] == 'S' && stack[top - 1] == '+' && stack[top] == 'S'){
            stack[top - 2] = 'S';
            stack[--top] = '\0';
            top--;
            printf("%s\t%s\tREDUCE (S -> S + S)\n", stack, expr + i);
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
    printf("S-> S + S\nS -> S * S\nS -> a\n\n");
    printf("Enter a valid expression to be parsed: ");
    char expr[100];
    scanf("%s", expr);

    printf("STACK\tINPUT\tACTION\n\n");
    shift(expr);

    if(top == 0 && stack[top] == 'S' && expr[i] == '\0'){
        printf("ACCEPTED\n");
    }
    else{
        printf("REJECTED\n");
    }
}