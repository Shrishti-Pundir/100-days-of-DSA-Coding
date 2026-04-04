/*Problem: Perform DFS starting from a given source vertex using recursion.

Input:
- n
- adjacency list
- starting vertex s

Output:
- DFS traversal order */


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

void DFS_iterative(struct Graph* graph, int start) {
    int* stack = (int*)malloc(graph->numVertices * sizeof(int));
    int top = -1;
    
    stack[++top] = start;
    
    while (top >= 0) {
        int vertex = stack[top--];
        
        if (!graph->visited[vertex]) {
            graph->visited[vertex] = 1;
            printf("%d ", vertex);
            
            struct Node* temp = graph->adjLists[vertex];
            while (temp) {
                if (!graph->visited[temp->vertex]) {
                    stack[++top] = temp->vertex;
                }
                temp = temp->next;
            }
        }
    }
    
    free(stack);
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
    
    printf("DFS traversal starting from vertex %d: ", s);
    DFS_iterative(graph, s);
    printf("\n");
    
    return 0;
}
