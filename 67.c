/*Problem: Print topological ordering of a Directed Acyclic Graph (DAG) using DFS.*/


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
    int* stack;
    int stackIndex;
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = V;
    graph->adjLists = (struct Node**)malloc(V * sizeof(struct Node*));
    graph->visited = (int*)calloc(V, sizeof(int));
    graph->stack = (int*)malloc(V * sizeof(int));
    graph->stackIndex = 0;
    
    for (int i = 0; i < V; i++) {
        graph->adjLists[i] = NULL;
    }
    
    return graph;
}

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = graph->adjLists[u];
    graph->adjLists[u] = newNode;
}

void dfs(struct Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    
    struct Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!graph->visited[adjVertex]) {
            dfs(graph, adjVertex);
        }
        temp = temp->next;
    }
    
    graph->stack[graph->stackIndex++] = vertex;
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);
    
    struct Graph* graph = createGraph(V);
    
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }
    
    for (int i = 0; i < V; i++) {
        if (!graph->visited[i]) {
            dfs(graph, i);
        }
    }
    
    printf("Topological Order: ");
    for (int i = graph->stackIndex - 1; i >= 0; i--) {
        printf("%d ", graph->stack[i]);
    }
    printf("\n");
    
    return 0;
}
