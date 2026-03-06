/*Problem: Implement a stack data structure using an array with the following operations: push, pop, and display.

Input:
- First line: integer n (number of operations)
- Next n lines: operation type and value (if applicable)
  - 1 value: push value
  - 2: pop
  - 3: display

Output:
- For display: print stack elements from top to bottom
- For pop: print popped element or 'Stack Underflow'

Example:
Input:
5
1 10
1 20
3
2
3

Output:
20 10
20
10*/


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

void pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return;
    }
    printf("%d\n", stack[top--]);
}

void display() {
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    
    for (int i = top; i >= 0; i--) {
        printf("%d", stack[i]);
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n, operation, value;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &operation);
        
        switch (operation) {
            case 1:  // push
                scanf("%d", &value);
                push(value);
                break;
                
            case 2:  // pop
                pop();
                break;
                
            case 3:  // display
                display();
                break;
                
            default:
                printf("Invalid operation\n");
        }
    }
    
    return 0;
}
