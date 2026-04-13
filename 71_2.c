/*You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

 

Example 1:


Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
Explanation: 

We can connect the points as shown above to get the minimum cost of 20.
Notice that there is a unique path between every pair of points.
Example 2:

Input: points = [[3,12],[-2,5],[-4,1]]
Output: 18
 

Constraints:

1 <= points.length <= 1000
-106 <= xi, yi <= 106
All pairs (xi, yi) are distinct. */


#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int u;
    int v;
    int dist;
} Edge;

int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->dist - ((Edge*)b)->dist;
}

int find(int* parent, int x) {
    if (parent[x] != x) {
        parent[x] = find(parent, parent[x]);
    }
    return parent[x];
}

void unionSet(int* parent, int* rank, int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    
    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize) {
    if (pointsSize <= 1) return 0;
    
    int totalEdges = pointsSize * (pointsSize - 1) / 2;
    Edge* edges = (Edge*)malloc(totalEdges * sizeof(Edge));
    int edgeCount = 0;
    
    for (int i = 0; i < pointsSize; i++) {
        for (int j = i + 1; j < pointsSize; j++) {
            int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            edges[edgeCount].u = i;
            edges[edgeCount].v = j;
            edges[edgeCount].dist = dist;
            edgeCount++;
        }
    }
    
    qsort(edges, totalEdges, sizeof(Edge), compareEdges);
    
    int* parent = (int*)malloc(pointsSize * sizeof(int));
    int* rank = (int*)calloc(pointsSize, sizeof(int));
    
    for (int i = 0; i < pointsSize; i++) {
        parent[i] = i;
    }
    
    int totalCost = 0;
    int edgesUsed = 0;
    
    for (int i = 0; i < totalEdges && edgesUsed < pointsSize - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        
        if (find(parent, u) != find(parent, v)) {
            unionSet(parent, rank, u, v);
            totalCost += edges[i].dist;
            edgesUsed++;
        }
    }
    
    free(edges);
    free(parent);
    free(rank);
    
    return totalCost;
}
