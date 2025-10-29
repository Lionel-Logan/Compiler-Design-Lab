#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
char expr[20];
char stack[20];
int top=-1;
int i=0;

void check(){
    while(1){
        if(top>=0 && stack[top]=='a'){
            stack[top]='S';
            printf("%s\t\t\t%s\n",stack,expr+i);
        }
        else if(top>=2 && stack[top-2]=='S' && stack[top-1]=='+' && stack[top]=='S'){
            top=top-2;
            stack[top]='S';
            stack[top+1]='\0';
            printf("%s\t\t\t%s\n",stack,expr+i);
        }
        else if(top>=2 && stack[top-2]=='S' && stack[top-1]=='*' && stack[top]=='S'){
            top=top-2;
            stack[top]='S';
            stack[top+1]='\0';
            printf("%s\t\t\t%s\n",stack,expr+i);
        }
        else{
            return;
        }
    }   
}

void main(){
    printf("enter the expr:");
    scanf("%s",expr);
    while(i<strlen(expr)){
        top=top+1;
        stack[top]=expr[i];
        stack[top+1]='\0';
        i=i+1;
        printf("%s\t\t\t%s\n",stack,expr+i);
        check();
    }

    if(top==0 && stack[top]=='S'){
        printf("accepted");
    }
    else{
        printf("not accepted");
    }
    
}