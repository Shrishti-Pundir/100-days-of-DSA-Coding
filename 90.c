/* Problem Statement
Given n boards of different lengths and k painters, each painter paints contiguous boards. Painting a unit length of board takes one unit of time.

Determine the minimum time required to paint all boards.

Input Format
n k
n space-separated integers representing board lengths

Output Format
Print the minimum time required to paint all boards.

Sample Input
4 2
10 20 30 40

Sample Output
60

Explanation
One painter paints boards of length 10, 20, and 30 (total 60), while the other paints board of length 40. */



```c
#include <stdio.h>
#include <stdlib.h>

int canPaint(int* boards, int n, int k, int maxTime) {
    int painters = 1;
    int sum = 0;
    
    for (int i = 0; i < n; i++) {
        if (boards[i] > maxTime) {
            return 0;
        }
        if (sum + boards[i] > maxTime) {
            painters++;
            sum = boards[i];
            if (painters > k) {
                return 0;
            }
        } else {
            sum += boards[i];
        }
    }
    return 1;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    int boards[100000];
    int totalLength = 0;
    int maxBoard = 0;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &boards[i]);
        totalLength += boards[i];
        if (boards[i] > maxBoard) {
            maxBoard = boards[i];
        }
    }
    
    int left = maxBoard;
    int right = totalLength;
    int result = totalLength;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canPaint(boards, n, k, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}
```
