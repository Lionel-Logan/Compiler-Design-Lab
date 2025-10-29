#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
char temp='Z';

char* intercode(char *expr,char c){
    int i=0;
    while(i<strlen(expr)){
        if(expr[i]==c){
            char a=expr[i-1];
            char b=expr[i+1];
            expr[i-1]=temp;
            printf("%c\t\t%c\t\t%c\t\t%c\n",c,temp,a,b);
            temp=temp-1;
            int j=i+2,k=i;
            while(expr[k]!='\0'){
                expr[k]=expr[j];
                k++;
                j++;
            }
            expr[k]='\0';
        }
        i++;
    }
    return strdup(expr);
}
void generate(char *expr){
    expr=intercode(expr,'/');
    expr=intercode(expr,'*');
    expr=intercode(expr,'+');
    expr=intercode(expr,'-');
    expr=intercode(expr,'=');
}
void main(){
    printf("enter the expression:");
    char expr[100];
    scanf("%s",expr);
    getchar();
    generate(expr);
}