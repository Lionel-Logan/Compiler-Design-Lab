#ifndef HASH_SET_H
#define HASH_SET_H

#include <stdbool.h>

typedef struct Set{
    char* key;
    struct Set* next;
} Set;

bool containsInSet(Set** head, char* key);
void putToSet(Set** head, char* key);
void removeFromSet(Set** head, char* key);
bool isSetEmpty(Set** head);

#endif