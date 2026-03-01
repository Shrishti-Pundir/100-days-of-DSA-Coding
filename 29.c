/*Problem: Rotate Linked List Right by k Places - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers
- Third line: integer k

Output:
- Print the linked list elements after rotation, space-separated

Example:
Input:
5
10 20 30 40 50
2

Output:
40 50 10 20 30

Explanation:
Connect last node to head forming circular list. Traverse to (n-k)th node, set next to NULL, update head to (n-k+1)th node.*/


#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int main() {
    int n, k;
    scanf("%d", &n);
    
    struct Node *head = NULL, *tail = NULL, *newnode = NULL;
    
    for (int i = 0; i < n; i++) {
        newnode = (struct Node*)malloc(sizeof(struct Node));
        scanf("%d", &newnode->data);
        newnode->next = NULL;
        
        if (head == NULL) {
            head = newnode;
            tail = newnode;
        } else {
            tail->next = newnode;
            tail = newnode;
        }
    }
    
    scanf("%d", &k);
    
    if (head == NULL || head->next == NULL || k % n == 0) {
        struct Node* temp = head;
        while (temp != NULL) {
            printf("%d", temp->data);
            if (temp->next != NULL) printf(" ");
            temp = temp->next;
        }
        printf("\n");
        
        temp = head;
        while (temp != NULL) {
            struct Node* next = temp->next;
            free(temp);
            temp = next;
        }
        return 0;
    }
    
    k = k % n;
    
    tail->next = head;
    
    int stepsToNewTail = n - k - 1;
    struct Node* newTail = head;
    for (int i = 0; i < stepsToNewTail; i++) {
        newTail = newTail->next;
    }
    
    struct Node* newHead = newTail->next;
    newTail->next = NULL;
    
    struct Node* temp = newHead;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" ");
        temp = temp->next;
    }
    printf("\n");
    
    temp = newHead;
    while (temp != NULL) {
        struct Node* next = temp->next;
        free(temp);
        temp = next;
    }
    
    return 0;
}
