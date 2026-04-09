/*Problem: Implement topological sorting using in-degree array and queue (Kahnâ€™s Algorithm). */

#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int numVertices;
    int** adj;
    int* indegree;
};

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = V;
    graph->adj = (int**)malloc(V * sizeof(int*));
    graph->indegree = (int*)calloc(V, sizeof(int));
    
    for (int i = 0; i < V; i++) {
        graph->adj[i] = (int*)calloc(V, sizeof(int));
    }
    
    return graph;
}

void addEdge(struct Graph* graph, int u, int v) {
    if (graph->adj[u][v] == 0) {
        graph->adj[u][v] = 1;
        graph->indegree[v]++;
    }
}

int* topologicalSort(struct Graph* graph, int V, int* resultSize) {
    int* queue = (int*)malloc(V * sizeof(int));
    int front = 0, rear = 0;
    
    for (int i = 0; i < V; i++) {
        if (graph->indegree[i] == 0) {
            queue[rear++] = i;
        }
    }
    
    int* result = (int*)malloc(V * sizeof(int));
    int index = 0;
    
    while (front < rear) {
        int vertex = queue[front++];
        result[index++] = vertex;
        
        for (int i = 0; i < V; i++) {
            if (graph->adj[vertex][i] == 1) {
                graph->indegree[i]--;
                if (graph->indegree[i] == 0) {
                    queue[rear++] = i;
                }
            }
        }
    }
    
    free(queue);
    
    if (index == V) {
        *resultSize = V;
        return result;
    } else {
        *resultSize = 0;
        free(result);
        return NULL;
    }
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
    
    int resultSize;
    int* result = topologicalSort(graph, V, &resultSize);
    
    if (resultSize > 0) {
        printf("Topological Order: ");
        for (int i = 0; i < resultSize; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("Cycle detected! Topological sorting not possible.\n");
    }
    
    for (int i = 0; i < V; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph->indegree);
    free(graph);
    
    return 0;
}
