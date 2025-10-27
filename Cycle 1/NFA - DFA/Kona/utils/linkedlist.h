#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct ListNode{
    char* val;
    struct ListNode* next;
} ListNode;

void addToList(ListNode** head, char* val);

#endif