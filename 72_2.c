/*Given a 2d matrix cost[][] of size n where cost[i][j] denotes the cost of moving from city i to city j. Your task is to complete a tour from city 0 (0-based index) to all other cities such that you visit each city exactly once and then at the end come back to city 0 at minimum cost.

Examples:

Input: cost[][] = [[0, 111], 
                [112, 0]]
Output: 223
Explanation: We can visit 0->1->0 and cost = 111 + 112.
Input: cost[][] = [[0, 1000, 5000],
                [5000, 0, 1000],
                [1000, 5000, 0]]
Output: 3000
Explanation: We can visit 0->1->2->0 and cost = 1000 + 1000 + 1000 = 3000
Constraints:
1 ≤ cost.size() ≤ 15
0 ≤ cost[i][j] ≤ 104 */


using System;

class Solution {
    public int tsp(int[,] cost) {
        int n = cost.GetLength(0);
        if (n == 0) return 0;
        
        int totalStates = 1 << n;
        int[,] dp = new int[totalStates, n];
        
        for (int i = 0; i < totalStates; i++) {
            for (int j = 0; j < n; j++) {
                dp[i, j] = int.MaxValue;
            }
        }
        
        dp[1, 0] = 0;
        
        for (int mask = 1; mask < totalStates; mask++) {
            for (int u = 0; u < n; u++) {
                if (dp[mask, u] == int.MaxValue) continue;
                
                for (int v = 0; v < n; v++) {
                    if ((mask & (1 << v)) != 0) continue;
                    
                    int newMask = mask | (1 << v);
                    int newCost = dp[mask, u] + cost[u, v];
                    
                    if (newCost < dp[newMask, v]) {
                        dp[newMask, v] = newCost;
                    }
                }
            }
        }
        
        int fullMask = totalStates - 1;
        int result = int.MaxValue;
        
        for (int u = 0; u < n; u++) {
            if (dp[fullMask, u] != int.MaxValue) {
                result = Math.Min(result, dp[fullMask, u] + cost[u, 0]);
            }
        }
        
        return result;
    }
}
