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
0 ≤ edges[i][0], edges[i][1] < V */

#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node, int parent, vector<int> adj[], vector<int>& vis) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        if (!vis[it]) {
            if (dfs(it, node, adj, vis)) return true;
        } else if (it != parent) {
            return true;
        }
    }
    return false;
}
}   
