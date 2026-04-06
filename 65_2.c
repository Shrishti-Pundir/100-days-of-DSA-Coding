/* Given an undirected graph with V vertices and E edges, represented as a 2D vector edges[][], where each entry edges[i] = [u, v] denotes an edge between vertices u and v, determine whether the graph contains a cycle or not.

Note: The graph can have multiple component.

Examples:

Input: V = 4, E = 4, edges[][] = [[0, 1], [0, 2], [1, 2], [2, 3]]
Output: true
Explanation: 
 
1 -> 2 -> 0 -> 1 is a cycle.
Input: V = 4, E = 3, edges[][] = [[0, 1], [1, 2], [2, 3]]
Output: false
Explanation: 
 
No cycle in the graph.
Constraints:
1 ≤ V, E ≤ 105
0 ≤ edges[i][0], edges[i][1] < V ***

bool dfs(int vertex, int parent, struct Node** adj, int* visited, int V) {
    visited[vertex] = 1;
    
    struct Node* temp = adj[vertex];
    while (temp) {
        int neighbor = temp->vertex;
        
        if (!visited[neighbor]) {
            if (dfs(neighbor, vertex, adj, visited, V)) {
                return true;
            }
        } else if (neighbor != parent) {
            return true;
        }
        
        temp = temp->next;
    }
    
    return false;
}

bool isCycle(int edges[][2], int E, int V) {
    struct Node** adj = (struct Node**)calloc(V, sizeof(struct Node*));
    
    for (int i = 0; i < E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->vertex = v;
        newNode->next = adj[u];
        adj[u] = newNode;
        
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->vertex = u;
        newNode->next = adj[v];
        adj[v] = newNode;
    }
    
    int* visited = (int*)calloc(V, sizeof(int));
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(i, -1, adj, visited, V)) {
                free(visited);
                return true;
            }
        }
    }
    
    free(visited);
    return false;
}   