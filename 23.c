/*Problem: Merge Two Sorted Linked Lists - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers (first list)
- Third line: integer m
- Fourth line: m space-separated integers (second list)

Output:
- Print the merged linked list elements, space-separated

Example:
Input:
5
10 20 30 40 50
4
15 25 35 45

Output:
10 15 20 25 30 35 40 45 50

Explanation:
Compare nodes of both lists, append smaller to result, continue until all nodes are merged.*/



#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createList(int n) {
    struct Node *head = NULL, *temp = NULL, *newnode = NULL;
    
    for (int i = 0; i < n; i++) {
        newnode = (struct Node*)malloc(sizeof(struct Node));
        scanf("%d", &newnode->data);
        newnode->next = NULL;
        
        if (head == NULL) {
            head = newnode;
            temp = newnode;
        } else {
            temp->next = newnode;
            temp = newnode;
        }
    }
    return head;
}

struct Node* mergeLists(struct Node* head1, struct Node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;
    
    struct Node* result = NULL;
    
    if (head1->data <= head2->data) {
        result = head1;
        result->next = mergeLists(head1->next, head2);
    } else {
        result = head2;
        result->next = mergeLists(head1, head2->next);
    }
    
    return result;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" ");
        }
        temp = temp->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int n, m;
    
    scanf("%d", &n);
    struct Node* list1 = createList(n);
    
    scanf("%d", &m);
    struct Node* list2 = createList(m);
    
    struct Node* merged = mergeLists(list1, list2);
    printList(merged);
    
    freeList(merged);
    
    return 0;
}