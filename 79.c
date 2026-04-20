/* Problem Statement
Find shortest distances from source vertex in a weighted graph with non-negative weights.

Input Format
n m
u v w
source

Output Format
Distances to all vertices.

Sample Input
5 6
1 2 2
1 3 4
2 3 1
2 4 7
3 5 3
4 5 1
1

Sample Output
0 2 3 9 6

Explanation
Shortest distances computed via priority queue. */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1000

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Node* addNode(struct Node* head, int v, int w) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = head;
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

void dijkstra(struct Node* adj[], int n, int source) {
    int* dist = (int*)malloc((n + 1) * sizeof(int));
    
    struct MinHeap* minHeap = createMinHeap(n);
    
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        minHeap->array[i - 1] = createMinHeapNode(i, dist[i]);
        minHeap->pos[i] = i - 1;
    }
    
    dist[source] = 0;
    decreaseKey(minHeap, source, dist[source]);
    minHeap->size = n;
    
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
    
    for (int i = 1; i <= n; i++) {
        printf("%d ", dist[i]);
    }
    printf("\n");
    
    free(dist);
    
    for (int i = 0; i < n; i++) {
        free(minHeap->array[i]);
    }
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    struct Node* adj[MAX] = {NULL};
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u] = addNode(adj[u], v, w);
        adj[v] = addNode(adj[v], u, w);
    }
    
    int source;
    scanf("%d", &source);
    
    dijkstra(adj, n, source);
    
    return 0;
}
