#include <stdio.h>
#include <string.h>

int tCount = 1;
char temp = 'Z';

char* generateCodeForOperator(char* expr, char op){
    int i = 0;
    while(expr[i] != '\0'){
        if(expr[i] == op){
            char ch1 = expr[i - 1];
            char ch2 = expr[i + 1];
            expr[i - 1] = temp;
            printf("%c = %c %c %c\n", temp, ch1, op, ch2);
            temp--;
            int j = i + 2, k = i;
            while(expr[j] != '\0'){
                expr[k++] = expr[j++];
            }
            expr[k] = '\0';
            continue;
        }
        i++;
    }
    return strdup(expr);
}

void generate(char* expr){
    expr = generateCodeForOperator(expr, '/');
    expr = generateCodeForOperator(expr, '*');
    expr = generateCodeForOperator(expr, '-');
    expr = generateCodeForOperator(expr, '+');
    printf("%c = %c\n", expr[0], expr[2]);
}

void main(){
    printf("Enter a valid expression (single letters only): ");
    char expr[100];
    scanf("%s", expr);

    printf("\n=======THREE ADDRESS CODE GENERATION=======\n\n");
    generate(expr);
}