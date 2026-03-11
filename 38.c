/* Problem: Deque (Double-Ended Queue)

A Deque is a linear data structure that allows insertion and deletion of elements from both the front and the rear. It provides more flexibility than a standard queue or stack.

Common Operations:
1. push_front(value): Insert an element at the front of the deque.
2. push_back(value): Insert an element at the rear of the deque.
3. pop_front(): Remove an element from the front of the deque.
4. pop_back(): Remove an element from the rear of the deque.
5. front(): Return the front element of the deque.
6. back(): Return the rear element of the deque.
7. empty(): Check whether the deque is empty.
8. size(): Return the number of elements in the deque.

Additional Operations:
- clear(): Remove all elements from the deque.
- erase(): Remove one or more elements from the deque.
- swap(): Swap contents of two deques.
- emplace_front(): Insert an element at the front without copying.
- emplace_back(): Insert an element at the rear without copying.
- resize(): Change the size of the deque.
- assign(): Replace elements with new values.
- reverse(): Reverse the order of elements.
- sort(): Sort the elements in ascending order.

Time Complexity:
- push_front, push_back, pop_front, pop_back, front, back, empty, size: O(1)
- clear, erase, resize, assign, reverse: O(n)
- sort: O(n log n)

Input:
- Sequence of deque operations with values (if applicable)

Output:
- Results of operations such as front, back, size, or the final state of the deque after all operations */


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

struct Deque {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int count;
};

struct Deque* createDeque() {
    struct Deque* dq = (struct Deque*)malloc(sizeof(struct Deque));
    dq->front = 0;
    dq->rear = -1;
    dq->count = 0;
    return dq;
}

int isFull(struct Deque* dq) {
    return dq->count == MAX_SIZE;
}

int isEmpty(struct Deque* dq) {
    return dq->count == 0;
}

void push_front(struct Deque* dq, int value) {
    if (isFull(dq)) {
        printf("Deque Overflow\n");
        return;
    }
    dq->front = (dq->front - 1 + MAX_SIZE) % MAX_SIZE;
    dq->arr[dq->front] = value;
    dq->count++;
}

void push_back(struct Deque* dq, int value) {
    if (isFull(dq)) {
        printf("Deque Overflow\n");
        return;
    }
    dq->rear = (dq->rear + 1) % MAX_SIZE;
    dq->arr[dq->rear] = value;
    dq->count++;
}

int pop_front(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow\n");
        return -1;
    }
    int value = dq->arr[dq->front];
    dq->front = (dq->front + 1) % MAX_SIZE;
    dq->count--;
    return value;
}

int pop_back(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow\n");
        return -1;
    }
    int value = dq->arr[dq->rear];
    dq->rear = (dq->rear - 1 + MAX_SIZE) % MAX_SIZE;
    dq->count--;
    return value;
}

int front(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return -1;
    }
    return dq->arr[dq->front];
}

int back(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return -1;
    }
    return dq->arr[dq->rear];
}

int size(struct Deque* dq) {
    return dq->count;
}

void display(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque: ");
    for (int i = 0; i < dq->count; i++) {
        int index = (dq->front + i) % MAX_SIZE;
        printf("%d ", dq->arr[index]);
    }
    printf("\n");
}

int main() {
    struct Deque* dq = createDeque();
    int choice, value;
    
    do {
        printf("\n1.push_front 2.push_back 3.pop_front 4.pop_back\n");
        printf("5.front 6.back 7.size 8.display 9.exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push_front(dq, value);
                display(dq);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                push_back(dq, value);
                display(dq);
                break;
            case 3:
                value = pop_front(dq);
                if (value != -1) printf("Popped: %d\n", value);
                display(dq);
                break;
            case 4:
                value = pop_back(dq);
                if (value != -1) printf("Popped: %d\n", value);
                display(dq);
                break;
            case 5:
                value = front(dq);
                if (value != -1) printf("Front: %d\n", value);
                break;
            case 6:
                value = back(dq);
                if (value != -1) printf("Back: %d\n", value);
                break;
            case 7:
                printf("Size: %d\n", size(dq));
                break;
            case 8:
                display(dq);
                break;
        }
    } while (choice != 9);
    
    free(dq);
    return 0;
}