/* There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some servers unable to reach some other server.

Return all critical connections in the network in any order.

 

Example 1:


Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.
Example 2:

Input: n = 2, connections = [[0,1]]
Output: [[0,1]]
 

Constraints:

2 <= n <= 105
n - 1 <= connections.length <= 105
0 <= ai, bi <= n - 1
ai != bi
There are no repeated connections. */



#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100005

typedef struct {
    int** edges;
    int* size;
    int* capacity;
} AdjList;

AdjList adj;
int discovery[MAX_N];
int low[MAX_N];
int visited[MAX_N];
int timer;

void addEdge(int u, int v) {
    if (adj.size[u] >= adj.capacity[u]) {
        adj.capacity[u] = adj.capacity[u] == 0 ? 4 : adj.capacity[u] * 2;
        adj.edges[u] = (int*)realloc(adj.edges[u], adj.capacity[u] * sizeof(int));
    }
    adj.edges[u][adj.size[u]++] = v;
}

void dfs(int u, int parent, int** result, int* resultCount, int* returnColumnSizes) {
    visited[u] = 1;
    discovery[u] = low[u] = ++timer;
    
    for (int i = 0; i < adj.size[u]; i++) {
        int v = adj.edges[u][i];
        
        if (!visited[v]) {
            dfs(v, u, result, resultCount, returnColumnSizes);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
            
            if (low[v] > discovery[u]) {
                result[*resultCount] = (int*)malloc(2 * sizeof(int));
                result[*resultCount][0] = u;
                result[*resultCount][1] = v;
                returnColumnSizes[*resultCount] = 2;
                (*resultCount)++;
            }
        } else if (v != parent) {
            low[u] = (low[u] < discovery[v]) ? low[u] : discovery[v];
        }
    }
}

int** criticalConnections(int n, int** connections, int connectionsSize, int* connectionsColSize, int* returnSize, int** returnColumnSizes) {
    adj.edges = (int**)malloc(n * sizeof(int*));
    adj.size = (int*)calloc(n, sizeof(int));
    adj.capacity = (int*)calloc(n, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        adj.edges[i] = NULL;
    }
    
    for (int i = 0; i < connectionsSize; i++) {
        int u = connections[i][0];
        int v = connections[i][1];
        
        addEdge(u, v);
        addEdge(v, u);
    }
    
    memset(visited, 0, sizeof(visited));
    memset(discovery, 0, sizeof(discovery));
    memset(low, 0, sizeof(low));
    timer = 0;
    
    int** result = (int**)malloc(connectionsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(connectionsSize * sizeof(int));
    *returnSize = 0;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, -1, result, returnSize, *returnColumnSizes);
        }
    }
    
    for (int i = 0; i < n; i++) {
        free(adj.edges[i]);
    }
    free(adj.edges);
    free(adj.size);
    free(adj.capacity);
    
    return result;
}
