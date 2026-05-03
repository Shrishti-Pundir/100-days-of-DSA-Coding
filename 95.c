/* Problem: Given n real numbers in [0,1), sort using bucket sort algorithm.
Distribute into buckets, sort each, concatenate. */



#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 10

struct Node {
    float data;
    struct Node* next;
};

void insertSorted(struct Node** bucket, float value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    
    if (*bucket == NULL || (*bucket)->data >= value) {
        newNode->next = *bucket;
        *bucket = newNode;
        return;
    }
    
    struct Node* current = *bucket;
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void bucketSort(float arr[], int n) {
    struct Node* buckets[BUCKET_SIZE];
    
    for (int i = 0; i < BUCKET_SIZE; i++) {
        buckets[i] = NULL;
    }
    
    for (int i = 0; i < n; i++) {
        int bucketIndex = (int)(arr[i] * BUCKET_SIZE);
        insertSorted(&buckets[bucketIndex], arr[i]);
    }
    
    int index = 0;
    for (int i = 0; i < BUCKET_SIZE; i++) {
        struct Node* current = buckets[i];
        while (current != NULL) {
            arr[index++] = current->data;
            current = current->next;
        }
    }
    
    for (int i = 0; i < BUCKET_SIZE; i++) {
        struct Node* current = buckets[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    float arr[1000];
    for (int i = 0; i < n; i++) {
        scanf("%f", &arr[i]);
    }
    
    bucketSort(arr, n);
    
    for (int i = 0; i < n; i++) {
        printf("%.2f", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    return 0;
}
