/*Problem: Queue Using Array - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n (number of elements)
- Second line: n space-separated integers

Output:
- Print queue elements from front to rear, space-separated

Example:
Input:
5
10 20 30 40 50

Output:
10 20 30 40 50

Explanation:
Use array and front/rear pointers. Enqueue inserts at rear, dequeue removes from front. Display from front to rear.*/


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
    return (q->front == -1);
}

int isFull(struct Queue* q) {
    return (q->rear == MAX_SIZE - 1);
}

void enqueue(struct Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    
    if (isEmpty(q)) {
        q->front = 0;
    }
    
    q->arr[++(q->rear)] = value;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    
    int value = q->arr[q->front];
    
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    
    return value;
}

void display(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d", q->arr[i]);
        if (i < q->rear) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n, value;
    scanf("%d", &n);
    
    struct Queue* q = createQueue();
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        enqueue(q, value);
    }
    
    display(q);
    
    free(q);
    
    return 0;
}
}
