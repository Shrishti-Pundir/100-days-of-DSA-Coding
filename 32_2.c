/*Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:

MinStack() initializes the stack object.
void push(int val) pushes the element val onto the stack.
void pop() removes the element on the top of the stack.
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.
You must implement a solution with O(1) time complexity for each function.

 

Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2  */



#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int val;
    int min;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} MinStack;


MinStack* minStackCreate() {
    MinStack* obj = (MinStack*)malloc(sizeof(MinStack));
    obj->top = NULL;
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->min = (obj->top == NULL) ? val : (val < obj->top->min ? val : obj->top->min);
    newNode->next = obj->top;
    obj->top = newNode;
}

void minStackPop(MinStack* obj) {
    if (obj->top == NULL) return;
    
    Node* temp = obj->top;
    obj->top = obj->top->next;
    free(temp);
}

int minStackTop(MinStack* obj) {
    return obj->top->val;
}

int minStackGetMin(MinStack* obj) {
    return obj->top->min;
}

void minStackFree(MinStack* obj) {
    while (obj->top != NULL) {
        Node* temp = obj->top;
        obj->top = obj->top->next;
        free(temp);
    }
    free(obj);
}
