#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Map* head = NULL;

Node* getFromMap(char *key){
    if(containsKeyInMap(key)){
        Map* temp = head;
        Node* node = NULL;
        while(temp != NULL){
            if(strcmp(temp -> key, key) == 0){
                return temp ->value;
            }
            temp = temp -> next;
        }
    }
    return NULL;
}

void putToMap(char *key, Node *value){
    Node* node = getFromMap(key);
    if(node == NULL){
        Map* temp = head;
        Map* mapNode = (Map*) malloc(sizeof(Map));
        mapNode -> key = strdup(key);
        mapNode -> value = value;
        mapNode -> next = NULL;
        if(head == NULL){
            head = mapNode;
            return;
        }
        while(temp -> next != NULL){
            temp = temp -> next;
        }
        temp -> next = mapNode;
    }
    else{
        node -> val = strdup(value -> val);
    }
}

bool containsKeyInMap(char *key){
    Map* temp = head;
    while(temp != NULL){
        if(strcmp(temp ->key, key) == 0){
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

bool isMapEmpty(){
    if(head == NULL){
        return true;
    }
    return false;
}
