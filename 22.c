/*Problem: Count Nodes in Linked List

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the result

Example:
Input:
5
10 20 30 40 50

Output:
10 20 30 40 50*/


#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int main() {
    int n;
    scanf("%d", &n);
    
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
    
    int count = 0;
    temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" ");
        }
        count++;
        temp = temp->next;
    }
    printf("\n");
    
    printf("Number of nodes: %d\n", count);
    
    temp = head;
    while (temp != NULL) {
        struct Node* next = temp->next;
        free(temp);
        temp = next;
    }
    
    return 0;
}
