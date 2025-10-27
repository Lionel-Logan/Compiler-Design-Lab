#include "queue.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Node* front = NULL;
Node* rear = NULL;

void offerToQueue(char* el){
    Node* node = (Node*) malloc(sizeof(Node));
    node -> val = strdup(el);
    node -> next = NULL;
    node -> children = NULL;
    node -> weights = NULL;
    if(front == NULL && rear == NULL){
        front = rear = node;
    }
    else{
        rear -> next = node;
        rear = node;
    }
}

char* pollFromQueue(){
    if(isQueueEmpty()){
        return NULL;
    }
    Node* node = front;
    front = front -> next;
    char* el = strdup(node -> val);
    free(node);
    if(front == NULL){
        rear = front = NULL;
    }
    return el;
}

char* peakFrontInQueue(){
    if(isQueueEmpty()){
        return NULL;
    }
    char* el = strdup(front -> val);
    return el;
}

char* peakRearInQueue(){
    if(isQueueEmpty()){
        return NULL;
    }
    char* el = strdup(rear -> val);
    return el;
}

bool isQueueEmpty(){
    if(front == NULL && rear == NULL){
        return true;
    }
    return false;
}