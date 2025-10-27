#include "linkedlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void addToList(ListNode** head, char* val){
    ListNode* node = (ListNode*) malloc(sizeof(ListNode));
    node -> val = strdup(val);
    node -> next = NULL;
    if(*head == NULL){
        *head = node;
        return;
    }
    ListNode* temp = *head;
    while(temp -> next != NULL){
        temp = temp -> next;
    }
    temp -> next = node;
}