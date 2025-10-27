#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node{
    char* state;
    struct Node* closure;
    struct Node* next;
} Node;

Node* head = NULL;

void displayInitialTranisitionTable(FILE* f){
    FILE* temp = f;
    char start[100], symbol[100], end[100];
    while(fscanf(f, "%s %s %s", start, symbol, end) == 3){
        printf("%s\t%s\t%s\n", start, symbol, end);
    }
    printf("\n");
    rewind(f);
}

void readStates(int n){
    Node* temp = head;
    for(int i = 0; i < n; i++){
        Node* node = (Node*) malloc(sizeof(Node));
        node -> next = NULL;
        node -> closure = (Node*) malloc(sizeof(Node));
        node -> closure -> next = NULL;
        printf(">>> ");
        char state[100];
        scanf("%s", state);
        node -> state = strdup(state);
        node -> closure -> state = strdup(state);
        if(head == NULL){
            head = temp = node;
        }
        else{
            temp -> next = node;
            temp = node;
        }
    }
}

bool closureDoesContain(char* init, char* end){
    Node* temp = head;
    while(temp != NULL){
        if(strcmp(temp -> state, init) == 0){
            Node* node = temp -> closure;
            while(node != NULL){
                if(strcmp(node -> state, end) == 0){
                    return true;
                }
                node = node -> next;
            }
        }
        temp = temp -> next;
    }
    return false;
}

void findEpsilonClosure(FILE* f, char* init, char* current){
    char start[100], symbol[100], end[100];
    rewind(f);
    while(fscanf(f, "%s %s %s", start, symbol, end) == 3){
        if(strcmp(start, current) == 0 && strcmp(symbol, "e") == 0){
            if(!closureDoesContain(init, end)){
                Node* node = (Node*) malloc(sizeof(Node));
                node -> state = strdup(end);
                node -> next = NULL;
                
                Node* temp = head;
                while(temp != NULL){
                    if(strcmp(temp -> state, init) == 0){
                        break;
                    }
                    temp = temp -> next;
                }
                
                Node* tClosure = temp -> closure;
                while(tClosure -> next != NULL){
                    tClosure = tClosure -> next;
                }
                tClosure -> next = node;
                findEpsilonClosure(f, init, end);
            }
        }
    }
}

void main(){
    printf("Enter the total number of states: ");
    int n;
    scanf("%d", &n);

    printf("Enter the state names as per the \"automata.txt\": \n\n");
    readStates(n);

    FILE* f = fopen("automata.txt", "r");
    printf("Reading contents from \"automata.txt\": \n\n");
    displayInitialTranisitionTable(f);

    printf("Generating Epsilon closures for all %d states: \n\n", n);
    Node* temp = head;
    while(temp != NULL){
        findEpsilonClosure(f, temp -> state, temp -> state);
        temp = temp -> next;
    }

    while(head != NULL){
        printf("E-Closure of %s: ", head -> state);
        while(head -> closure != NULL){
            printf("%s ", head -> closure -> state);
            head -> closure = head -> closure -> next;
        }
        printf("\n");
        head = head -> next;
    }
}