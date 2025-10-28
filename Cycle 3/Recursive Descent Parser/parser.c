#include <stdio.h>
#include <stdbool.h>

char input[100];
int i = 0;

bool E();
bool Eprime();
bool T();
bool Tprime();
bool F();

bool match(char ch){
    if(input[i] == ch){
        i++;
        return true;
    }
    return false;
}

// E -> T E'
bool E(){
    printf("E -> T E'\n");
    if(T()){
        if(Eprime()){
            return true;
        }
    }
    return false;
}

// E' -> + T E' | ε
bool Eprime(){
    if(input[i] == '+'){
        printf("E' -> + T E'\n");
        if(match('+')){
            if(T()){
                if(Eprime()){
                    return true;
                }
            }
        }
        return false;
    }
    printf("E' -> ε\n");
    return true;
}

// T -> F T'
bool T(){
    printf("T -> F T'\n");
    if(F()){
        if(Tprime()){
            return true;
        }
    }
    return false;
}

// T' -> * F T' | ε
bool Tprime(){
    if(input[i] == '*'){
        printf("T' -> * F T'\n");
        if(match('*')){
            if(F()){
                if(Tprime()) return true;
            }
        }
        return false;
    }
    printf("T' -> ε\n");
    return true;
}

// F -> (E) | i
bool F(){
    if(input[i] == '('){
        printf("F -> (E)\n");
        if(match('(')){
            if(E()){
                if(match(')')){
                    return true;
                }
            }
        }
        return false;
    } 
    printf("F -> i\n");
    if(match('i')){
        return true;
    }
    return false;
}

int main(){
    printf("======= RECURSIVE DESCENT PARSER =======\n\n");
    printf("Grammar:\n");
    printf("E -> T E'\nE' -> + T E' | ε\nT -> F T'\nT' -> * F T' | ε\nF -> (E) | i\n\n");

    printf("Enter input string: ");
    scanf("%s", input);

    bool result = E();
    if(result && input[i] == '\0')
        printf("String Accepted!\n");
    else
        printf("String Rejected!\n");
    return 0;
}