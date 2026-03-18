/*Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.
Notes:

You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.
 

Example 1:

Input
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 1, 1, false]

Explanation
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false*/





#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack {
    int* data;
    int top;
    int capacity;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = 100;
    stack->data = (int*)malloc(sizeof(int) * stack->capacity);
    stack->top = -1;
    return stack;
}

void stackPush(Stack* stack, int x) {
    stack->data[++stack->top] = x;
}

int stackPop(Stack* stack) {
    return stack->data[stack->top--];
}

int stackTop(Stack* stack) {
    return stack->data[stack->top];
}

bool stackEmpty(Stack* stack) {
    return stack->top == -1;
}

void stackFree(Stack* stack) {
    free(stack->data);
    free(stack);
}

typedef struct {
    Stack* input;
    Stack* output;
} MyQueue;

MyQueue* myQueueCreate() {
    MyQueue* queue = (MyQueue*)malloc(sizeof(MyQueue));
    queue->input = createStack();
    queue->output = createStack();
    return queue;
}

void myQueuePush(MyQueue* obj, int x) {
    stackPush(obj->input, x);
}

void transfer(MyQueue* obj) {
    if (stackEmpty(obj->output)) {
        while (!stackEmpty(obj->input)) {
            stackPush(obj->output, stackPop(obj->input));
        }
    }
}

int myQueuePop(MyQueue* obj) {
    transfer(obj);
    return stackPop(obj->output);
}

int myQueuePeek(MyQueue* obj) {
    transfer(obj);
    return stackTop(obj->output);
}

bool myQueueEmpty(MyQueue* obj) {
    return stackEmpty(obj->input) && stackEmpty(obj->output);
}

void myQueueFree(MyQueue* obj) {
    stackFree(obj->input);
    stackFree(obj->output);
    free(obj);
}
