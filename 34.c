/*Problem: Evaluate Postfix Expression - Implement using linked list with dynamic memory allocation.

Input:
- Postfix expression with operands and operators

Output:
- Print the integer result

Example:
Input:
2 3 1 * + 9 -

Output:
-4

Explanation:
Use stack to store operands, apply operators by popping operands, push result back. Final stack top is result.*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* push(struct Node* top, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = top;
    return newNode;
}

struct Node* pop(struct Node* top, int* value) {
    if (top == NULL) {
        return NULL;
    }
    *value = top->data;
    struct Node* temp = top;
    top = top->next;
    free(temp);
    return top;
}

int evaluatePostfix(char* exp) {
    struct Node* stack = NULL;
    char* token = strtok(exp, " ");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            stack = push(stack, atoi(token));
        } else {
            int val1, val2;
            stack = pop(stack, &val2);
            stack = pop(stack, &val1);
            
            switch (token[0]) {
                case '+': stack = push(stack, val1 + val2); break;
                case '-': stack = push(stack, val1 - val2); break;
                case '*': stack = push(stack, val1 * val2); break;
                case '/': stack = push(stack, val1 / val2); break;
                default: break;
            }
        }
        token = strtok(NULL, " ");
    }
    
    int result;
    stack = pop(stack, &result);
    return result;
}

int main() {
    char exp[1000];
    fgets(exp, sizeof(exp), stdin);
    exp[strcspn(exp, "\n")] = 0;
    
    int result = evaluatePostfix(exp);
    printf("%d\n", result);
    
    return 0;
}
