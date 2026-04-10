/*You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.

 

Example 1:


Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2
Example 2:

Input: times = [[1,2,1]], n = 2, k = 1
Output: 1
Example 3:

Input: times = [[1,2,1]], n = 2, k = 2
Output: -1
 

Constraints:

1 <= k <= n <= 100
1 <= times.length <= 6000
times[i].length == 3
1 <= ui, vi <= n
ui != vi
0 <= wi <= 100
All the pairs (ui, vi) are unique. (i.e., no multiple edges.) */


#include <stdlib.h>
#include <limits.h>

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Node* createNode(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct MinHeapNode {
    int vertex;
    int dist;
};

struct MinHeap {
    int size;
    int capacity;
    int* pos;
    struct MinHeapNode** array;
};

struct MinHeapNode* createMinHeapNode(int vertex, int dist) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->vertex = vertex;
    node->dist = dist;
    return node;
}

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int*)malloc((capacity + 1) * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc((capacity + 1) * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist) {
        smallest = left;
    }
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist) {
        smallest = right;
    }
    
    if (smallest != idx) {
        struct MinHeapNode* smallestNode = minHeap->array[smallest];
        struct MinHeapNode* idxNode = minHeap->array[idx];
        
        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;
        
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return NULL;
    }
    
    struct MinHeapNode* root = minHeap->array[0];
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    
    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;
    
    minHeap->size--;
    minHeapify(minHeap, 0);
    
    return root;
}

void decreaseKey(struct MinHeap* minHeap, int vertex, int dist) {
    int i = minHeap->pos[vertex];
    minHeap->array[i]->dist = dist;
    
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int isInMinHeap(struct MinHeap* minHeap, int vertex) {
    return minHeap->pos[vertex] < minHeap->size;
}

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k) {
    struct Node** adj = (struct Node**)malloc((n + 1) * sizeof(struct Node*));
    for (int i = 1; i <= n; i++) {
        adj[i] = NULL;
    }
    
    for (int i = 0; i < timesSize; i++) {
        int u = times[i][0];
        int v = times[i][1];
        int w = times[i][2];
        
        struct Node* newNode = createNode(v, w);
        newNode->next = adj[u];
        adj[u] = newNode;
    }
    
    int* dist = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[k] = 0;
    
    struct MinHeap* minHeap = createMinHeap(n);
    for (int i = 1; i <= n; i++) {
        minHeap->array[i - 1] = createMinHeapNode(i, dist[i]);
        minHeap->pos[i] = i - 1;
    }
    minHeap->size = n;
    
    decreaseKey(minHeap, k, dist[k]);
    
    while (!isEmpty(minHeap)) {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;
        free(minHeapNode);
        
        struct Node* temp = adj[u];
        while (temp) {
            int v = temp->vertex;
            int w = temp->weight;
            
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                decreaseKey(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
    }
    
    int maxTime = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) {
            maxTime = -1;
            break;
        }
        if (dist[i] > maxTime) {
            maxTime = dist[i];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        struct Node* temp = adj[i];
        while (temp) {
            struct Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(adj);
    free(dist);
    
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
    
    return maxTime;
}
