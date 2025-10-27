#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node{
    char* val;
    struct Node* first;
    struct Node* follow;
    struct Node* next;
} Node;

Node* head = NULL;

/*
displayProductions() - Reads and displays productions from the file
displayFirst() - Displays the first of all productions
displayFollow() - Display the follow of all productions

readNonTerminals() - Reads non-terminals for a given production

isNonTerminal() - Checks if the input is a non-terminal
containsTerminalInFirst() - Checks if terminal exists in First
containsTerminalInFollow() - Checks if terminal exists in Follow

addToFirst() - add terminal to First
addToFollow() - add terminal to Follow
addFirstToFollow() - add First to Follow
addFollowToFollow() - add Follow to Follow

findFirst() - Computational logic for finding First
findFollow() - Computational logic for finding Follow
*/

// Display Methods
void displayProductions(FILE* f){
    char symbol[100], production[100];
    while(fscanf(f, "%s -> %s", symbol, production) == 2){
        printf("%s -> %s\n", symbol, production);
    }
    printf("\n");
    rewind(f);
}

void displayFirst(){
    Node* temp = head;
    while(temp != NULL){
        printf("FIRST(%s): ", temp -> val);
        Node* tFirst = temp -> first;
        while(tFirst != NULL){
            printf("%s ", tFirst -> val);
            tFirst = tFirst -> next;
        }
        printf("\n");
        temp = temp -> next;
    }
    printf("\n");
}

void displayFollow(){
    Node* temp = head;
    while(temp != NULL){
        printf("FOLLOW(%s): ", temp -> val);
        Node* tFollow = temp -> follow;
        while(tFollow != NULL){
            printf("%s ", tFollow -> val);
            tFollow = tFollow -> next;
        }
        printf("\n");
        temp = temp -> next;
    }
    printf("\n");
}

// Read Methods
void readNonTerminals(int n){
    Node* temp = head;
    for(int i = 0; i < n; i++){
        printf(">>> ");
        char nonTerminal[100];
        scanf("%s", nonTerminal);

        Node* node  = (Node*) malloc(sizeof(Node));
        node -> val = strdup(nonTerminal);
        node -> first = NULL;
        node -> follow = NULL;
        node -> next = NULL;

        if(head == NULL){
            head = temp = node;
        }
        else{
            temp -> next = node;
            temp = node;
        }
    }
    printf("\n");
}

// Helper Methods
bool isNonTerminal(char* nonTerminal){
    Node* temp = head;
    while(temp != NULL){
        if(strcmp(temp -> val, nonTerminal) == 0){
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

bool containsTerminalInFirst(char* init, char* terminal){
    Node* temp = head;
    while(temp != NULL){
        if(strcmp(temp -> val, init) == 0){
            Node* tFirst = temp -> first;
            while(tFirst != NULL){
                if(strcmp(tFirst -> val, terminal) == 0){
                    return true;
                }
                tFirst = tFirst -> next;
            }
        }
        temp = temp -> next;
    }
    return false;
}

bool containsTerminalInFollow(char* init, char* terminal){
    Node* temp = head;
    while(temp != NULL){
        if(strcmp(temp -> val, init) == 0){
            Node* tFollow = temp -> follow;
            while(tFollow != NULL){
                if(strcmp(tFollow -> val, terminal) == 0){
                    return true;
                }
                tFollow = tFollow -> next;
            }
        }
        temp = temp -> next;
    }
    return false;
}

void addToFirst(char* init, char* terminal){
    Node* temp = head;
    Node* node = (Node*) malloc(sizeof(Node));
    node -> val = strdup(terminal);
    node -> next = NULL;
    while(temp != NULL){
        if(strcmp(temp -> val, init) == 0){
            if(temp -> first == NULL){
                temp -> first = node;
                return;
            }
            Node* tFirst = temp -> first;
            while(tFirst -> next != NULL){
                tFirst = tFirst -> next;
            }
            tFirst -> next = node;
            return;
        }
        temp = temp -> next;
    }
}

void addToFollow(char* init, char* terminal){
    Node* temp = head;
    Node* node = (Node*) malloc(sizeof(Node));
    node -> val = strdup(terminal);
    node -> next = NULL;
    while(temp != NULL){
        if(strcmp(temp -> val, init) == 0){
            if(temp -> follow == NULL){
                temp -> follow = node;
                return;
            }
            Node* tFollow = temp -> follow;
            while(tFollow -> next != NULL){
                tFollow = tFollow -> next;
            }
            tFollow -> next = node;
            return;
        }
        temp = temp -> next;
    }
}

bool addFirstToFollow(char* firstOf, char* followOf){
    Node* temp = head;
    Node* first = NULL;
    bool containsEpsilon = false;
    while(temp != NULL){
        if(strcmp(temp -> val, firstOf) == 0){
            first = temp -> first;
            break;
        }
        temp = temp -> next;
    }

    temp = first;
    while(temp != NULL){
        if(!containsTerminalInFollow(followOf, temp -> val)){
            if(strcmp(temp -> val, "#") == 0){
                containsEpsilon = true;
            }
            else{
                addToFollow(followOf, temp -> val);
            }
        }
        temp = temp -> next;
    }

    return containsEpsilon;
}

void addFollowToFollow(char* followOf, char* followTo){
    Node* temp = head;
    Node* follow = NULL;
    while(temp != NULL){
        if(strcmp(temp -> val, followOf) == 0){
            follow = temp -> follow;
            break;
        }
        temp = temp -> next;
    }

    temp = follow;
    while(temp != NULL){
        if(!containsTerminalInFollow(followTo, temp -> val)){
            addToFollow(followTo, temp -> val);
        }
        temp = temp -> next;
    }
}

// Computational Methods
void findFirst(FILE* f, char* init, char* current){
    rewind(f);
    char symbol[100], production[100];
    while(fscanf(f, "%s -> %s", symbol, production) == 2){
        if(strcmp(symbol, current) == 0){
            int i = 0;
            while(production[i] != '\0'){
                char buffer[2];
                buffer[0] = production[i];
                buffer[1] = '\0';
                if(isNonTerminal(buffer)){
                    findFirst(f, buffer, buffer);
                    Node* temp = head;
                    while(temp != NULL){
                        if(strcmp(temp -> val, buffer) == 0){
                            Node* tFirst = temp -> first;
                            while(tFirst != NULL){
                                if(!containsTerminalInFirst(init, tFirst -> val)){
                                    addToFirst(init, tFirst -> val);
                                }
                                tFirst = tFirst -> next;
                            }
                            break;
                        }
                        temp = temp -> next;
                    }
                    if(containsTerminalInFirst(buffer, "#")){
                        i++;
                        continue;
                    }
                    else{
                        break;
                    }
                }
                else{
                    if(!containsTerminalInFirst(init, buffer)){
                        addToFirst(init, buffer);
                    }
                    break;
                }
            }

            if(production[i] == '\0'){
                if(!containsTerminalInFirst(init, "#")){
                    addToFirst(init, "#");
                }
            }
        }
    }
}

void findFollow(FILE* f, char* init){
    rewind(f);
    char symbol[100], production[100];
    while(fscanf(f, "%s -> %s", symbol, production) == 2){
        int i = 0;
        char buffer[2];
        while(production[i] != '\0'){
            buffer[0] = production[i];
            buffer[1] = '\0';
            if(strcmp(buffer, init) == 0){
                break;
            }
            i++;
        }
        if(production[i] == '\0'){
            continue;
        }
        i++;
        while(production[i] != '\0'){
            char value[2];
            value[0] = production[i];
            value[1] = '\0';
            if(!isNonTerminal(value)){
                if(!containsTerminalInFollow(init, value)){
                    addToFollow(init, value);
                }
                break;
            }
            else{
                bool containsEpsilon = addFirstToFollow(value, init);
                if(containsEpsilon){
                    i++;
                    continue;
                }
                else{
                    break;
                }
            }
        }
        if(production[i] == '\0'){
            findFollow(f, symbol);
            addFollowToFollow(symbol, init);
        }
    }
}

// Main Method
void main(){
    FILE* f = fopen("grammar.txt", "r");

    printf("Reading the productions from \"productions.txt\": \n\n");
    displayProductions(f);

    printf("Enter the total number of non-terminals: ");
    int nonTerminals;
    scanf("%d", &nonTerminals);
    readNonTerminals(nonTerminals);

    Node* temp = head;
    while(temp != NULL){
        findFirst(f, temp -> val, temp -> val);
        temp = temp -> next;
    }

    temp = head;
    printf("Enter the starting production non-terminal: ");
    char start[100];
    scanf("%s", start);
    while(temp != NULL){
        if(strcmp(start, temp -> val) == 0){
            addToFollow(start, "$");
        }
        findFollow(f, temp -> val);
        temp = temp -> next;
    }

    printf("=======FIRST OF %d PRODUCTIONS=======\n\n", nonTerminals);
    displayFirst();
    printf("=======FOLLOW OF %d PRODUCTIONS=======\n\n", nonTerminals);
    displayFollow();
}