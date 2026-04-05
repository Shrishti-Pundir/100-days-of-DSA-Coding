/*You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

 

Example 1:


Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:

Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:

Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0. */


#include <stdlib.h>

int orangesRotting(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    
    int queue[10000][2];
    int front = 0, rear = 0;
    int fresh = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 2) {
                queue[rear][0] = i;
                queue[rear][1] = j;
                rear++;
            } else if (grid[i][j] == 1) {
                fresh++;
            }
        }
    }
    
    if (fresh == 0) {
        return 0;
    }
    
    int minutes = -1;
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    while (front < rear) {
        int size = rear - front;
        minutes++;
        
        for (int i = 0; i < size; i++) {
            int r = queue[front][0];
            int c = queue[front][1];
            front++;
            
            for (int d = 0; d < 4; d++) {
                int nr = r + dirs[d][0];
                int nc = c + dirs[d][1];
                
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                    grid[nr][nc] = 2;
                    queue[rear][0] = nr;
                    queue[rear][1] = nc;
                    rear++;
                    fresh--;
                }
            }
        }
    }
    
    return (fresh == 0) ? minutes : -1;
}
