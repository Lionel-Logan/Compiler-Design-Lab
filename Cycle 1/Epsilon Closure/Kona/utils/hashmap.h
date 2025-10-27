#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "queue.h"
#include <stdbool.h>

typedef struct Map{
    char* key;
    Node* value;
    struct Map* next;
} Map;

extern Map* head;

Node* getFromMap(char* key);
void putToMap(char* key, Node* value);
bool containsKeyInMap(char* key);
bool isMapEmpty();

#endif