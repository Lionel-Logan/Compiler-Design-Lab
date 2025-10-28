#include <stdio.h>
#include <stdbool.h>

char input[100];
int i = 0;

bool E();
bool EPrime();

bool matches(char ch){
    if(input[i] == ch){
        i++;
        return true;
    }
    return false;
}

bool E(){
    if(matches('i')){
        printf("E -> iE'\n");
        if(EPrime()){
            return true;
        }
    }
    return false;
}

bool EPrime(){
    if(matches('+')){
        printf("E -> +iE'\n");
        if(matches('i')){
            if(EPrime()){
                return true;
            }
        }
    }

    printf("E -> e\n");
}

void main(){
    printf("======= RECURSIVE DESCENT PARSER =======\n\n");
    printf("Grammar:\n");
    printf("E -> iE'\nE' -> +iE' | e\n\n");

    printf("Enter input string: ");
    scanf("%s", input);

    bool result = E();
    if(result && input[i] == '\0'){
        printf("String Accepted!\n");
    }
    else{
        printf("String Rejected!\n");
    }
}