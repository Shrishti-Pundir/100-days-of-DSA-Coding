/*Problem: Compute shortest path from source and detect negative weight cycles using Bellman-Ford.

Input:
- n vertices
- m edges (u,v,w)

Output:
- Shortest distances OR NEGATIVE CYCLE */



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge {
    int src;
    int dest;
    int weight;
};

void bellmanFord(int V, int E, struct Edge* edges, int source) {
    int* dist = (int*)malloc(V * sizeof(int));
    
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[source] = 0;
    
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;
            
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;
        
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("NEGATIVE CYCLE\n");
            free(dist);
            return;
        }
    }
    
    printf("Shortest distances from vertex %d:\n", source);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("Vertex %d: INF\n", i);
        } else {
            printf("Vertex %d: %d\n", i, dist[i]);
        }
    }
    
    free(dist);
}

int main() {
    int V, E, source;
    scanf("%d %d", &V, &E);
    
    struct Edge* edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }
    
    scanf("%d", &source);
    
    bellmanFord(V, E, edges, source);
    
    free(edges);
    return 0;
}