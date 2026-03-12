/*Problem Statement:
Implement a Min Heap using an array where the smallest element is always at the root.

Supported Operations:
- insert x
- extractMin
- peek

Input Format:
- First line contains integer N
- Next N lines contain heap operations

Output Format:
- Print results of extractMin and peek
- Print -1 if operation cannot be performed

Example:
Input:
6
insert 40
insert 10
insert 30
peek
extractMin
peek

Output:
10
10
30*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

struct MinHeap {
    int arr[MAX_SIZE];
    int size;
};

struct MinHeap* createHeap() {
    struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    heap->size = 0;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(struct MinHeap* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->arr[parent] > heap->arr[index]) {
            swap(&heap->arr[parent], &heap->arr[index]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(struct MinHeap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < heap->size && heap->arr[left] < heap->arr[smallest]) {
        smallest = left;
    }
    
    if (right < heap->size && heap->arr[right] < heap->arr[smallest]) {
        smallest = right;
    }
    
    if (smallest != index) {
        swap(&heap->arr[index], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

void insert(struct MinHeap* heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap Overflow\n");
        return;
    }
    
    heap->arr[heap->size] = value;
    heapifyUp(heap, heap->size);
    heap->size++;
}

int extractMin(struct MinHeap* heap) {
    if (heap->size == 0) {
        return -1;
    }
    
    int minValue = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    
    return minValue;
}

int peek(struct MinHeap* heap) {
    if (heap->size == 0) {
        return -1;
    }
    return heap->arr[0];
}

int main() {
    int n;
    scanf("%d", &n);
    
    struct MinHeap* heap = createHeap();
    
    for (int i = 0; i < n; i++) {
        char operation[20];
        scanf("%s", operation);
        
        if (strcmp(operation, "insert") == 0) {
            int value;
            scanf("%d", &value);
            insert(heap, value);
        }
        else if (strcmp(operation, "extractMin") == 0) {
            int result = extractMin(heap);
            printf("%d\n", result);
        }
        else if (strcmp(operation, "peek") == 0) {
            int result = peek(heap);
            printf("%d\n", result);
        }
    }
    
    free(heap);
    
    return 0;
}

