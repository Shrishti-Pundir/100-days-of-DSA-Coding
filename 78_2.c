/* Given an undirected connected graph with V vertices and adjacency list adj. You are required to find all the vertices removing which (and edges through it) disconnects the graph into 2 or more components and return it in sorted manner.
Note: Indexing is zero-based i.e nodes numbering from (0 to V-1). There might be loops present in the graph.

Example 1:

Input:

Output:{1,4}
Explanation: Removing the vertex 1 will
discconect the graph as-

Removing the vertex 4 will disconnect the
graph as-

 

Your Task:
You don't need to read or print anything. Your task is to complete the function articulationPoints() which takes V and adj as input parameters and returns a list containing all the vertices removing which turn the graph into two or more disconnected components in sorted order. If there are no such vertices then returns a list containing -1.
 

Expected Time Complexity: O(V + E)
Expected Auxiliary Space: O(V)
 

Constraints:
1 ≤ V ≤ 105 */



int timer;

void dfsAP(int node, int parent, int visited[], int disc[], int low[], int mark[], int adj[105][105], int n) {
    visited[node] = 1;
    disc[node] = low[node] = timer++;
    int child = 0;

    for(int v = 0; v < n; v++) {
        if(adj[node][v] == 0)
            continue;

        if(v == parent)
            continue;

        if(!visited[v]) {
            dfsAP(v, node, visited, disc, low, mark, adj, n);
            if(low[v] < low[node])
                low[node] = low[v];

            if(low[v] >= disc[node] && parent != -1)
                mark[node] = 1;

            child++;
        }
        else {
            if(disc[v] < low[node])
                low[node] = disc[v];
        }
    }

    if(parent == -1 && child > 1)
        mark[node] = 1;
}
