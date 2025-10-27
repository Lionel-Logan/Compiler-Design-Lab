#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashset.h"

bool containsInSet(Set** head, char* key){
    if(isSetEmpty(head)){
        return false;
    }
    Set* temp = *head;
    while(temp != NULL){
        if(strcmp(key, temp -> key) == 0){
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

void putToSet(Set** head, char* key){
    if(containsInSet(head, key)){
        return;
    }
    Set* node = (Set*) malloc(sizeof(Set));
    node -> key = strdup(key);
    node -> next = NULL;
    if(*head == NULL){
        *head = node;
        return;
    }
    Set* temp = *head;
    while(temp -> next != NULL){
        temp = temp -> next;
    }
    temp -> next = node;
}

void removeFromSet(Set** head, char* key){
    if(!containsInSet(head, key)){
        return;
    }
    if((*head) -> next == NULL){
        free((*head) -> key);
        free(*head);
        *head = NULL;
        return;
    }
    Set* temp = *head;
    Set* prev = NULL;
    while(temp != NULL){
        if(strcmp(temp -> key, key) == 0){
            break;
        }
        prev = temp;
        temp = temp -> next;
    }
    if(temp == NULL)
        return;
    if(prev == NULL){
        *head = (*head) -> next;
    }
    else{
        prev -> next = temp -> next;
        free(temp -> key);
        free(temp);
    }
}

bool isSetEmpty(Set** head){
    if(*head == NULL){
        return true;
    }
    return false;
}