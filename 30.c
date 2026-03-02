/*Problem: Polynomial Using Linked List - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n (number of terms)
- Next n lines: two integers (coefficient and exponent)

Output:
- Print polynomial in standard form, e.g., 10x^4 + 20x^3 + 30x^2 + 40x + 50

Example:
Input:
5
10 4
20 3
30 2
40 1
50 0

Output:
10x^4 + 20x^3 + 30x^2 + 40x + 50

Explanation:
Each node stores coefficient and exponent. Traverse nodes to print polynomial in decreasing exponent order.*/


#include <stdio.h>
#include <stdlib.h>

struct Term {
    int coeff;
    int exp;
    struct Term* next;
};

int main() {
    int n;
    scanf("%d", &n);
    
    struct Term *head = NULL, *tail = NULL, *newnode = NULL;
    
    for (int i = 0; i < n; i++) {
        newnode = (struct Term*)malloc(sizeof(struct Term));
        scanf("%d %d", &newnode->coeff, &newnode->exp);
        newnode->next = NULL;
        
        if (head == NULL) {
            head = newnode;
            tail = newnode;
        } else {
            tail->next = newnode;
            tail = newnode;
        }
    }
    
    struct Term* temp = head;
    while (temp != NULL) {
        printf("%dx^%d", temp->coeff, temp->exp);
        
        if (temp->next != NULL) {
            printf(" + ");
        }
        temp = temp->next;
    }
    printf("\n");
    
    temp = head;
    while (temp != NULL) {
        struct Term* next = temp->next;
        free(temp);
        temp = next;
    }
    
    return 0;
}
