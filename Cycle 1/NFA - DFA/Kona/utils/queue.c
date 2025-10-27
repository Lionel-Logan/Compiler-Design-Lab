#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

void offerToQueue(Queue** front, Queue** rear, char* val){
    Queue* node = (Queue*) malloc(sizeof(Queue));
    node -> val = strdup(val);
    node -> next = NULL;
    if(isQueueEmpty(front, rear)){
        *front = *rear = node;
        return;
    }
    (*rear) -> next = node;
    *rear = node;
}

char* pollFromQueue(Queue** front, Queue** rear){
    if(isQueueEmpty(front, rear)){
        return NULL;
    }
    Queue* temp = *front;
    *front = (*front) -> next;
    char* val = strdup(temp -> val);
    free(temp);
    if(*front == NULL){
        *front = *rear = NULL;
    }
    return val;
}

bool isQueueEmpty(Queue** front, Queue** rear){
    if(*front == NULL && *rear == NULL){
        return true;
    }
    return false;
}