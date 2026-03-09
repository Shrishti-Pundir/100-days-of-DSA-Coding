/* Problem: Circular Queue Using Array - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n (number of elements to enqueue)
- Second line: n space-separated integers
- Third line: integer m (number of dequeue operations)

Output:
- Print queue elements from front to rear after operations, space-separated

Example:
Input:
5
10 20 30 40 50
2

Output:
30 40 50 10 20

Explanation:
Use array and front/rear pointers. Rear wraps around to start after reaching array end. Dequeue removes elements from front. Display remaining elements in correct order. */


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

struct CircularQueue {
    int arr[MAX_SIZE];
    int front;
    int rear;
};

struct CircularQueue* createQueue() {
    struct CircularQueue* q = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct CircularQueue* q) {
    return (q->front == -1);
}

int isFull(struct CircularQueue* q) {
    return ((q->rear + 1) % MAX_SIZE == q->front);
}

void enqueue(struct CircularQueue* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
    
    q->arr[q->rear] = value;
}

int dequeue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    
    int value = q->arr[q->front];
    
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    
    return value;
}

void display(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    
    int i = q->front;
    while (1) {
        printf("%d", q->arr[i]);
        if (i == q->rear) {
            break;
        }
        printf(" ");
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}

int main() {
    int n, m, value;
    scanf("%d", &n);
    
    struct CircularQueue* q = createQueue();
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        enqueue(q, value);
    }
    
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        dequeue(q);
    }
    
    display(q);
    
    free(q);
    
    return 0;
}