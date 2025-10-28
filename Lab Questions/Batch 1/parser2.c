/*
    Write a C program to implement the shift reduce parser for the following:

    E -> E + T | T
    T -> T * F | F
    F ->(E) | id
*/

#include <stdio.h>
#include <stdbool.h>

char stack[100], input[100];
int top = -1, i = 0;

void reduce();

void shift(){
    while(input[i] != '\0'){
        if(input[i] == 'i' && input[i + 1] == 'd'){
            stack[++top] = 'I';
            stack[top + 1] = '\0';
            i += 2;
        }
        else{
            stack[++top] = input[i];
            stack[top + 1] = '\0';
            i++;
        }
        printf("%s\t%s\tSHIFT\n", stack, input + i);
        reduce();
    }
    printf("\n");
}

void reduce(){
    bool isReduced = true;
    while(isReduced){
        isReduced = false;
        // F -> id
        if(top >= 0 && stack[top] == 'I'){
            stack[top] = 'F';
            stack[top + 1] = '\0';
            printf("%s\t%s\tREDUCE (F -> id)\n", stack, input + i);
            isReduced = true;
        }
        // F -> (E)
        else if(top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')'){
            stack[top - 2] = 'F';
            stack[--top] = '\0';
            top--;
            printf("%s\t%s\tREDUCE (F -> (E))\n", stack, input + i);
            isReduced = true;
        }
        // T -> T * F
        else if(top >= 2 && stack[top - 2] == 'T' && stack[top - 1] == '*' && stack[top] == 'F'){
            stack[top - 2] = 'T';
            stack[--top] = '\0';
            top--;
            printf("%s\t%s\tREDUCE (T -> T * F)\n", stack, input + i);
            isReduced = true;
        }
        // T -> F
        else if(top >= 0 && stack[top] == 'F'){
            stack[top] = 'T';
            stack[top + 1] = '\0';
            printf("%s\t%s\tREDUCE (T -> F)\n", stack, input + i);
            isReduced = true;
        }
        // E -> E + T
        else if(top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'T'){
            stack[top - 2] = 'E';
            stack[--top] = '\0';
            top--;
            printf("%s\t%s\tREDUCE (E -> E + T)\n", stack, input + i);
            isReduced = true;
        }
        // E -> T
        else if(top >= 0 && stack[top] == 'T'){
            stack[top] = 'E';
            stack[top + 1] = '\0';
            printf("%s\t%s\tREDUCE (E -> T)\n", stack, input + i);
            isReduced = true;
        }
    }
}

void main(){
    printf("Consider the following grammar: \n\n");
    printf("E -> E + T | T\nT -> T * F | F\nF -> (E) | id\n\n");
    printf("Enter an expression that is to be parsed by the prescribed grammar: ");
    scanf("%s", input);

    printf("STACK\tINPUT\tACTION\n\n");
    shift();
    if(input[i] == '\0' && top == 0 && stack[top] == 'E'){
        printf("ACCEPT");
    }
    else{
        printf("%d %c\n",top, stack[top-1]);
        printf("ERROR");
    }
    printf("\n");
}