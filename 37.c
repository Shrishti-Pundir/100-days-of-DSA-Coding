/* Problem Statement:
Implement a Priority Queue using an array. An element with smaller value has higher priority.

Supported Operations:
- insert x
- delete
- peek

Input Format:
- First line contains integer N
- Next N lines contain operations

Output Format:
- Print the deleted or peeked element
- Print -1 if the queue is empty

Example:
Input:
5
insert 30
insert 10
insert 20
delete
peek

Output:
10
20 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

struct PriorityQueue {
    int arr[MAX_SIZE];
    int size;
};

struct PriorityQueue* createQueue() {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->size = 0;
    return pq;
}

void insert(struct PriorityQueue* pq, int value) {
    if (pq->size >= MAX_SIZE) {
        printf("Queue Overflow\n");
        return;
    }
    
    pq->arr[pq->size] = value;
    pq->size++;
}

int deleteMin(struct PriorityQueue* pq) {
    if (pq->size == 0) {
        return -1;
    }
    
    int minIndex = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->arr[i] < pq->arr[minIndex]) {
            minIndex = i;
        }
    }
    
    int minValue = pq->arr[minIndex];
    
    for (int i = minIndex; i < pq->size - 1; i++) {
        pq->arr[i] = pq->arr[i + 1];
    }
    
    pq->size--;
    return minValue;
}

int peek(struct PriorityQueue* pq) {
    if (pq->size == 0) {
        return -1;
    }
    
    int minValue = pq->arr[0];
    for (int i = 1; i < pq->size; i++) {
        if (pq->arr[i] < minValue) {
            minValue = pq->arr[i];
        }
    }
    
    return minValue;
}

int main() {
    int n;
    scanf("%d", &n);
    
    struct PriorityQueue* pq = createQueue();
    
    for (int i = 0; i < n; i++) {
        char operation[10];
        scanf("%s", operation);
        
        if (strcmp(operation, "insert") == 0) {
            int value;
            scanf("%d", &value);
            insert(pq, value);
        }
        else if (strcmp(operation, "delete") == 0) {
            int result = deleteMin(pq);
            if (result != -1) {
                printf("%d\n", result);
            } else {
                printf("-1\n");
            }
        }
        else if (strcmp(operation, "peek") == 0) {
            int result = peek(pq);
            if (result != -1) {
                printf("%d\n", result);
            } else {
                printf("-1\n");
            }
        }
    }
    
    free(pq);
    
    return 0;
}

