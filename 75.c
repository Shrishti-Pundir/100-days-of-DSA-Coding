/* Problem Statement
Given an array of integers containing both positive and negative values, find the length of the longest contiguous subarray whose sum is equal to zero.

Input Format
An integer array arr[].

Output Format
Print the length of the longest subarray with sum equal to zero.

Sample Input
15 -2 2 -8 1 7 10 23

Sample Output
5

Explanation
The subarray [-2, 2, -8, 1, 7] has a sum of 0 and is the longest such subarray. */


#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

Node* hashTable[MAX];

int hash(int key) {
    return (key % MAX + MAX) % MAX;
}

void insert(int key, int value) {
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

int search(int key) {
    int index = hash(key);
    Node* temp = hashTable[index];
    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;
}

void freeHashTable() {
    for (int i = 0; i < MAX; i++) {
        Node* temp = hashTable[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
}

int main() {
    int arr[1000];
    int n = 0;
    
    while (scanf("%d", &arr[n]) == 1) {
        n++;
    }
    
    for (int i = 0; i < MAX; i++) {
        hashTable[i] = NULL;
    }
    
    int maxLen = 0;
    int prefixSum = 0;
    
    insert(0, -1);
    
    for (int i = 0; i < n; i++) {
        prefixSum += arr[i];
        
        int prevIndex = search(prefixSum);
        
        if (prevIndex != -1) {
            int len = i - prevIndex;
            if (len > maxLen) {
                maxLen = len;
            }
        } else {
            insert(prefixSum, i);
        }
    }
    
    printf("%d\n", maxLen);
    
    freeHashTable();
    
    return 0;
}