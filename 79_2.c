/* Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges. The graph is represented as a 2D vector edges[][], where each entry edges[i] = [u, v] denotes a direct edge from vertex u to v. Find the number of strongly connected components in the graph.

Examples:

Input: V = 5, E = 5, edges[][] = [[0, 2], [0, 3], [1, 0], [2, 1], [3, 4]]


Output: 3
Explanation: We can clearly see that there are 3 Strongly Connected Components in the Graph.
 
Input: V = 3, E = 3, edges[][] = [[0, 1], [1, 2], [2, 0]]

Output: 1
Explanation: All of the nodes are connected to each other. So, there's only one SCC.
Input: V = 2, E = 1, edges[][] = [[0, 1]]
Output: 2
Constraints:
1 ≤ V ≤ 106
0 ≤ E ≤ 106
0 ≤ edges[i][0], edges[i][1] < V */


void dfs1(int node, int visited[], int graph[105][105], int n, int stack[], int* top) {
    visited[node] = 1;
    for(int i = 0; i < n; i++) {
        if(graph[node][i] && !visited[i])
            dfs1(i, visited, graph, n, stack, top);
    }
    stack[(*top)++] = node;
}

void dfs2(int node, int visited[], int rev[105][105], int n) {
    visited[node] = 1;
    for(int i = 0; i < n; i++) {
        if(rev[node][i] && !visited[i])
            dfs2(i, visited, rev, n);
    }
}
