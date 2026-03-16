/*Problem Statement:
Given a queue of integers, reverse the queue using a stack.

Input Format:
- First line contains integer N
- Second line contains N space-separated integers

Output Format:
- Print the reversed queue

Example:
Input:
5
10 20 30 40 50

Output:
50 40 30 20 10*/



#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

struct Queue {
    int arr[MAX_SIZE];
    int front;
    int rear;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct Queue* q) {
    return q->front == -1;
}

void enqueue(struct Queue* q, int value) {
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear++;
    }
    q->arr[q->rear] = value;
}

int dequeue(struct Queue* q) {
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return value;
}

int main() {
    int n;
    scanf("%d", &n);
    
    struct Queue* q = createQueue();
    int stack[MAX_SIZE];
    int top = -1;
    
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        enqueue(q, val);
    }
    
    while (!isEmpty(q)) {
        stack[++top] = dequeue(q);
    }
    
    while (top >= 0) {
        printf("%d", stack[top--]);
        if (top >= 0) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(q);
    return 0;
}