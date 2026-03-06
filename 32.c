/*Problem: Implement push and pop operations on a stack and verify stack operations.

Input:
- First line: integer n
- Second line: n integers to push
- Third line: integer m (number of pops)

Output:
- Print remaining stack elements from top to bottom

Example:
Input:
5
10 20 30 40 50
2

Output:
30 20 10*/


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int stack[MAX_SIZE];
int top = -1;

void push(int value) {
    if (top >= MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = value;
}

int pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

int main() {
    int n, m, value;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        push(value);
    }
    
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        pop();
    }
    
    if (top == -1) {
        printf("Stack is empty\n");
    } else {
        for (int i = top; i >= 0; i--) {
            printf("%d", stack[i]);
            if (i > 0) {
                printf(" ");
            }
        }
        printf("\n");
    }
    
    return 0;
}
