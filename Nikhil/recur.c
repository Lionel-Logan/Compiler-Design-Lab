#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

char input[30];
int ip=0;
char expr[30]="E";

void e();
void eprime();
void t();
void tprime();
void f();

void replacement(char nonterm,char *rhs){
    char temp[30]="";
    int replaced=0;
    int j=0;
    for(int i=0;expr[i]!='\0';i++){
        if(replaced==0 && expr[i]==nonterm){
            for(int k=0;rhs[k]!='\0';k++){
                temp[j]=rhs[k];
                j++;
            }
            replaced=1;
        }
        else{
            temp[j]=expr[i];
            j++;
        }
    }
    temp[j]='\0';
    strcpy(expr,temp);
    printf("%s\n",expr);
}

void e(){
    replacement('E',"TZ");
    t();
    eprime();
}

void eprime(){
    if(input[ip]=='+'){
        ip=ip+1;
        replacement('Z',"+TZ");
        t();
        eprime();
    }
    else{
        replacement('Z',"");
        return;
    }
}

void t(){
    replacement('T',"FY");
    f();
    tprime();
}

void tprime(){
    if(input[ip]=='*'){
        ip++;
        replacement('Y',"*FY");
        f();
        tprime();
    }
    else{
        replacement('Y',"");
        return;
    }
}

void f(){
    if(input[ip]=='('){
        ip++;
        replacement('F',"(E)");
        e();
        if(input[ip]==')'){
            ip++;
        }
    }
    else if (input[ip]=='i'){
        ip++;
        replacement('F',"i");
    }
}
void main(){
    printf("enter the input:(enter with $ at last)");
    scanf("%s",input);
    e();
    if (input[ip]=='$'){
        printf("accepted");
    }
    else{
        printf("not accepted");
    }
}