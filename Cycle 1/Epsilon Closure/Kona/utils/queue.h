#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "linkedlist.h"

typedef struct Node{
    char* val;
    struct ListNode * children;
    struct ListNode* weights;
    struct Node* next;
} Node;

extern Node* front;
extern Node* rear;

void offerToQueue(char* el);       
char* pollFromQueue();        
char* peakFrontInQueue();   
char* peakRearInQueue();    
bool isQueueEmpty();             

#endif