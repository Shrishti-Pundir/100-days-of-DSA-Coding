/*Problem Statement
Implement a hash table using quadratic probing with formula:

h(k, i) = (h(k) + i*i) % m

Input Format
Same as previous.

Output Format
Result of SEARCH operations.

Sample Input
7
4
INSERT 49
INSERT 56
SEARCH 49
SEARCH 15

Sample Output
FOUND
NOT FOUND

Explanation
Collisions resolved using i² jumps. */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -1
#define DELETED -2

int* hashTable;
int m;

int hashFunction(int key) {
    return key % m;
}

void insert(int key) {
    int index = hashFunction(key);
    int i = 0;
    
    while (hashTable[(index + i * i) % m] != EMPTY && 
           hashTable[(index + i * i) % m] != DELETED && 
           i < m) {
        i++;
    }
    
    if (i == m) {
        printf("Hash Table Full\n");
        return;
    }
    
    hashTable[(index + i * i) % m] = key;
}

int search(int key) {
    int index = hashFunction(key);
    int i = 0;
    
    while (hashTable[(index + i * i) % m] != EMPTY && i < m) {
        if (hashTable[(index + i * i) % m] == key) {
            return 1;
        }
        i++;
    }
    
    return 0;
}

void delete(int key) {
    int index = hashFunction(key);
    int i = 0;
    
    while (hashTable[(index + i * i) % m] != EMPTY && i < m) {
        if (hashTable[(index + i * i) % m] == key) {
            hashTable[(index + i * i) % m] = DELETED;
            return;
        }
        i++;
    }
}

int main() {
    int n, q;
    scanf("%d", &m);
    scanf("%d", &q);
    
    hashTable = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        hashTable[i] = EMPTY;
    }
    
    for (int i = 0; i < q; i++) {
        char operation[10];
        int key;
        scanf("%s %d", operation, &key);
        
        if (strcmp(operation, "INSERT") == 0) {
            insert(key);
        } else if (strcmp(operation, "SEARCH") == 0) {
            if (search(key)) {
                printf("FOUND\n");
            } else {
                printf("NOT FOUND\n");
            }
        } else if (strcmp(operation, "DELETE") == 0) {
            delete(key);
        }
    }
    
    free(hashTable);
    return 0;
}
