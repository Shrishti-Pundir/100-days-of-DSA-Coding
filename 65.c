/*Problem: Using DFS and parent tracking, detect if undirected graph has a cycle.

Output:
- YES or NO */



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
    int* parent;
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
    graph->parent = (int*)malloc(V * sizeof(int));
    
    for (int i = 0; i < V; i++) {
        graph->adjLists[i] = NULL;
        graph->parent[i] = -1;
    }
    
    return graph;
}

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = graph->adjLists[u];
    graph->adjLists[u] = newNode;
    
    newNode = createNode(u);
    newNode->next = graph->adjLists[v];
    graph->adjLists[v] = newNode;
}

bool dfs(struct Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    
    struct Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        
        if (!graph->visited[adjVertex]) {
            graph->parent[adjVertex] = vertex;
            if (dfs(graph, adjVertex)) {
                return true;
            }
        } else if (adjVertex != graph->parent[vertex]) {
            return true;
        }
        
        temp = temp->next;
    }
    
    return false;
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
    
    bool hasCycle = false;
    
    for (int i = 0; i < V; i++) {
        if (!graph->visited[i]) {
            if (dfs(graph, i)) {
                hasCycle = true;
                break;
            }
        }
    }
    
    if (hasCycle) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    
    return 0;
}