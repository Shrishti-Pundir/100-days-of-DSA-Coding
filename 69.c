/*Problem: Given weighted graph with non-negative edges, compute shortest path from source using priority queue.*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 1000

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
};

struct Node* createNode(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = V;
    graph->adjLists = (struct Node**)malloc(V * sizeof(struct Node*));
    
    for (int i = 0; i < V; i++) {
        graph->adjLists[i] = NULL;
    }
    
    return graph;
}

void addEdge(struct Graph* graph, int u, int v, int weight) {
    struct Node* newNode = createNode(v, weight);
    newNode->next = graph->adjLists[u];
    graph->adjLists[u] = newNode;
    
    // For undirected graph, add reverse edge
    newNode = createNode(u, weight);
    newNode->next = graph->adjLists[v];
    graph->adjLists[v] = newNode;
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
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
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

void dijkstra(struct Graph* graph, int source) {
    int V = graph->numVertices;
    int* dist = (int*)malloc(V * sizeof(int));
    
    struct MinHeap* minHeap = createMinHeap(V);
    
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        minHeap->array[i] = createMinHeapNode(i, dist[i]);
        minHeap->pos[i] = i;
    }
    
    dist[source] = 0;
    decreaseKey(minHeap, source, dist[source]);
    minHeap->size = V;
    
    while (!isEmpty(minHeap)) {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;
        
        struct Node* temp = graph->adjLists[u];
        while (temp) {
            int v = temp->vertex;
            
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
        free(minHeapNode);
    }
    
    printf("Shortest distances from source %d:\n", source);
    for (int i = 0; i < V; i++) {
        printf("Vertex %d: %d\n", i, dist[i]);
    }
    
    for (int i = 0; i < V; i++) {
        free(minHeap->array[i]);
    }
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
    free(dist);
}

int main() {
    int V, E, source;
    scanf("%d %d", &V, &E);
    
    struct Graph* graph = createGraph(V);
    
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(graph, u, v, w);
    }
    
    scanf("%d", &source);
    
    dijkstra(graph, source);
    
    return 0;
}
