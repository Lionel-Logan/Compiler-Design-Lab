#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/hashmap.h"
#include "utils/queue.h"
#include "utils/linkedlist.h"

int main() {
    printf("Enter total number of states: ");
    int n;
    scanf("%d", &n);

    ListNode* listHead = NULL;

    printf("Enter states:\n");
    for (int i = 0; i < n; i++) {
        printf(">>> ");
        char state[50];
        scanf("%s", state);

        Node* node = (Node*) malloc(sizeof(Node));
        node->val = strdup(state);
        node->children = NULL;
        node->weights = NULL;
        node->next = NULL;

        putToMap(state, node);
        addToList(&listHead, state);
    }

    printf("\nEnter total number of transitions: ");
    int t;
    scanf("%d", &t);

    printf("Enter transitions (start symbol end):\n");
    for (int i = 0; i < t; i++) {
        printf("Transition %d: ", i + 1);
        char start[50], symbol[50], end[50];
        scanf("%s", start);
        scanf("%s", symbol);
        scanf("%s", end);

        Node* nStart = getFromMap(start);
        Node* nEnd = getFromMap(end);
        if (nStart && nEnd) {
            addToList(&(nStart->children), nEnd->val);
            addToList(&(nStart->weights), symbol);
        }
    }

    printf("\n--- Epsilon Closures ---\n");
    ListNode* temp = listHead;
    while (temp != NULL) {
        printf("ε-closure(%s): %s ", temp->val, temp -> val);
        offerToQueue(temp->val);

        while (!isQueueEmpty()) {
            char* end = pollFromQueue();
            Node* node = getFromMap(end);
            if (!node) continue;

            ListNode* tC = node->children;
            ListNode* tW = node->weights;

            while (tC != NULL && tW != NULL) {
                if (strcmp(tW->val, "e") == 0) {
                    printf("%s ", tC->val);
                }
                offerToQueue(tC->val);
                tC = tC->next;
                tW = tW->next;
            }
        }
        printf("\n");
        temp = temp->next;
    }

    return 0;
}