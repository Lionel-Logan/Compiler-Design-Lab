#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct QueueNode{
    char* val;
    struct QueueNode* next;
} Queue;

void offerToQueue(Queue** front, Queue** rear, char* val);
char* pollFromQueue(Queue** front, Queue** rear);
bool isQueueEmpty(Queue** front, Queue** rear);

#endif