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



```c
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

void clear(struct Deque* dq) {
    dq->front = 0;
    dq->rear = -1;
    dq->count = 0;
}

void erase(struct Deque* dq, int position) {
    if (position < 0 || position >= dq->count) {
        printf("Invalid position\n");
        return;
    }
    
    int index = (dq->front + position) % MAX_SIZE;
    
    for (int i = position; i < dq->count - 1; i++) {
        int current = (dq->front + i) % MAX_SIZE;
        int next = (dq->front + i + 1) % MAX_SIZE;
        dq->arr[current] = dq->arr[next];
    }
    
    dq->rear = (dq->rear - 1 + MAX_SIZE) % MAX_SIZE;
    dq->count--;
}

void swap(struct Deque* dq1, struct Deque* dq2) {
    struct Deque temp = *dq1;
    *dq1 = *dq2;
    *dq2 = temp;
}

void resize(struct Deque* dq, int newSize) {
    if (newSize < 0 || newSize > MAX_SIZE) {
        printf("Invalid size\n");
        return;
    }
    
    if (newSize < dq->count) {
        dq->count = newSize;
        dq->rear = (dq->front + newSize - 1) % MAX_SIZE;
    } else if (newSize > dq->count) {
        for (int i = dq->count; i < newSize; i++) {
            push_back(dq, 0);
        }
    }
}

void assign(struct Deque* dq, int* values, int n) {
    clear(dq);
    for (int i = 0; i < n; i++) {
        push_back(dq, values[i]);
    }
}

void reverse(struct Deque* dq) {
    int i = 0, j = dq->count - 1;
    while (i < j) {
        int leftIndex = (dq->front + i) % MAX_SIZE;
        int rightIndex = (dq->front + j) % MAX_SIZE;
        
        int temp = dq->arr[leftIndex];
        dq->arr[leftIndex] = dq->arr[rightIndex];
        dq->arr[rightIndex] = temp;
        
        i++;
        j--;
    }
}

void sort(struct Deque* dq) {
    int temp[MAX_SIZE];
    for (int i = 0; i < dq->count; i++) {
        int index = (dq->front + i) % MAX_SIZE;
        temp[i] = dq->arr[index];
    }
    
    for (int i = 0; i < dq->count - 1; i++) {
        for (int j = 0; j < dq->count - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }
    
    for (int i = 0; i < dq->count; i++) {
        int index = (dq->front + i) % MAX_SIZE;
        dq->arr[index] = temp[i];
    }
}

void display(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return;
    }
    
    printf("Deque elements (front to rear): ");
    for (int i = 0; i < dq->count; i++) {
        int index = (dq->front + i) % MAX_SIZE;
        printf("%d", dq->arr[index]);
        if (i < dq->count - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    struct Deque* dq = createDeque();
    int choice, value, position, n;
    
    do {
        printf("\n--- Deque Operations ---\n");
        printf("1. push_front\n");
        printf("2. push_back\n");
        printf("3. pop_front\n");
        printf("4. pop_back\n");
        printf("5. front\n");
        printf("6. back\n");
        printf("7. empty\n");
        printf("8. size\n");
        printf("9. clear\n");
        printf("10. erase at position\n");
        printf("11. resize\n");
        printf("12. reverse\n");
        printf("13. sort\n");
        printf("14. display\n");
        printf("15. exit\n");
        printf("Enter your choice: ");
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
                if (value != -1) {
                    printf("Popped from front: %d\n", value);
                }
                display(dq);
                break;
                
            case 4:
                value = pop_back(dq);
                if (value != -1) {
                    printf("Popped from back: %d\n", value);
                }
                display(dq);
                break;
                
            case 5:
                value = front(dq);
                if (value != -1) {
                    printf("Front element: %d\n", value);
                }
                break;
                
            case 6:
                value = back(dq);
                if (value != -1) {
                    printf("Back element: %d\n", value);
                }
                break;
                
            case 7:
                printf(isEmpty(dq) ? "Deque is empty\n" : "Deque is not empty\n");
                break;
                
            case 8:
                printf("Size: %d\n", size(dq));
                break;
                
            case 9:
                clear(dq);
                printf("Deque cleared\n");
                break;
                
            case 10:
                printf("Enter position to erase (0-based): ");
                scanf("%d", &position);
                erase(dq, position);
                display(dq);
                break;
                
            case 11:
                printf("Enter new size: ");
                scanf("%d", &n);
                resize(dq, n);
                display(dq);
                break;
                
            case 12:
                reverse(dq);
                printf("Deque reversed\n");
                display(dq);
                break;
                
            case 13:
                sort(dq);
                printf("Deque sorted\n");
                display(dq);
                break;
                
            case 14:
                display(dq);
                break;
                
            case 15:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 15);
    
    free(dq);
    return 0;
}
```Problem: Deque (Double-Ended Queue)

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

void clear(struct Deque* dq) {
    dq->front = 0;
    dq->rear = -1;
    dq->count = 0;
}

void erase(struct Deque* dq, int position) {
    if (position < 0 || position >= dq->count) {
        printf("Invalid position\n");
        return;
    }
    
    int index = (dq->front + position) % MAX_SIZE;
    
    for (int i = position; i < dq->count - 1; i++) {
        int current = (dq->front + i) % MAX_SIZE;
        int next = (dq->front + i + 1) % MAX_SIZE;
        dq->arr[current] = dq->arr[next];
    }
    
    dq->rear = (dq->rear - 1 + MAX_SIZE) % MAX_SIZE;
    dq->count--;
}

void swap(struct Deque* dq1, struct Deque* dq2) {
    struct Deque temp = *dq1;
    *dq1 = *dq2;
    *dq2 = temp;
}

void resize(struct Deque* dq, int newSize) {
    if (newSize < 0 || newSize > MAX_SIZE) {
        printf("Invalid size\n");
        return;
    }
    
    if (newSize < dq->count) {
        dq->count = newSize;
        dq->rear = (dq->front + newSize - 1) % MAX_SIZE;
    } else if (newSize > dq->count) {
        for (int i = dq->count; i < newSize; i++) {
            push_back(dq, 0);
        }
    }
}

void assign(struct Deque* dq, int* values, int n) {
    clear(dq);
    for (int i = 0; i < n; i++) {
        push_back(dq, values[i]);
    }
}

void reverse(struct Deque* dq) {
    int i = 0, j = dq->count - 1;
    while (i < j) {
        int leftIndex = (dq->front + i) % MAX_SIZE;
        int rightIndex = (dq->front + j) % MAX_SIZE;
        
        int temp = dq->arr[leftIndex];
        dq->arr[leftIndex] = dq->arr[rightIndex];
        dq->arr[rightIndex] = temp;
        
        i++;
        j--;
    }
}

void sort(struct Deque* dq) {
    int temp[MAX_SIZE];
    for (int i = 0; i < dq->count; i++) {
        int index = (dq->front + i) % MAX_SIZE;
        temp[i] = dq->arr[index];
    }
    
    for (int i = 0; i < dq->count - 1; i++) {
        for (int j = 0; j < dq->count - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }
    
    for (int i = 0; i < dq->count; i++) {
        int index = (dq->front + i) % MAX_SIZE;
        dq->arr[index] = temp[i];
    }
}

void display(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return;
    }
    
    printf("Deque elements (front to rear): ");
    for (int i = 0; i < dq->count; i++) {
        int index = (dq->front + i) % MAX_SIZE;
        printf("%d", dq->arr[index]);
        if (i < dq->count - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    struct Deque* dq = createDeque();
    int choice, value, position, n;
    
    do {
        printf("\n--- Deque Operations ---\n");
        printf("1. push_front\n");
        printf("2. push_back\n");
        printf("3. pop_front\n");
        printf("4. pop_back\n");
        printf("5. front\n");
        printf("6. back\n");
        printf("7. empty\n");
        printf("8. size\n");
        printf("9. clear\n");
        printf("10. erase at position\n");
        printf("11. resize\n");
        printf("12. reverse\n");
        printf("13. sort\n");
        printf("14. display\n");
        printf("15. exit\n");
        printf("Enter your choice: ");
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
                if (value != -1) {
                    printf("Popped from front: %d\n", value);
                }
                display(dq);
                break;
                
            case 4:
                value = pop_back(dq);
                if (value != -1) {
                    printf("Popped from back: %d\n", value);
                }
                display(dq);
                break;
                
            case 5:
                value = front(dq);
                if (value != -1) {
                    printf("Front element: %d\n", value);
                }
                break;
                
            case 6:
                value = back(dq);
                if (value != -1) {
                    printf("Back element: %d\n", value);
                }
                break;
                
            case 7:
                printf(isEmpty(dq) ? "Deque is empty\n" : "Deque is not empty\n");
                break;
                
            case 8:
                printf("Size: %d\n", size(dq));
                break;
                
            case 9:
                clear(dq);
                printf("Deque cleared\n");
                break;
                
            case 10:
                printf("Enter position to erase (0-based): ");
                scanf("%d", &position);
                erase(dq, position);
                display(dq);
                break;
                
            case 11:
                printf("Enter new size: ");
                scanf("%d", &n);
                resize(dq, n);
                display(dq);
                break;
                
            case 12:
                reverse(dq);
                printf("Deque reversed\n");
                display(dq);
                break;
                
            case 13:
                sort(dq);
                printf("Deque sorted\n");
                display(dq);
                break;
                
            case 14:
                display(dq);
                break;
                
            case 15:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 15);
    
    free(dq);
    return 0;
}
