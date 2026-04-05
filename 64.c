/*Problem: Perform BFS from a given source using queue.

Input:
- n
- adjacency list
- source s

Output:
- BFS traversal order*/


#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*)calloc(vertices, sizeof(int));
    
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void BFS(struct Graph* graph, int start) {
    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;
    
    graph->visited[start] = 1;
    queue[rear++] = start;
    
    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);
        
        struct Node* temp = graph->adjLists[vertex];
        while (temp) {
            int connectedVertex = temp->vertex;
            if (!graph->visited[connectedVertex]) {
                graph->visited[connectedVertex] = 1;
                queue[rear++] = connectedVertex;
            }
            temp = temp->next;
        }
    }
    
    free(queue);
}

int main() {
    int n, m, s;
    scanf("%d %d", &n, &m);
    
    struct Graph* graph = createGraph(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }
    
    scanf("%d", &s);
    
    printf("BFS traversal starting from vertex %d: ", s);
    BFS(graph, s);
    printf("\n");
    
    return 0;
}
