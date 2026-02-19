/*Problem: Given an array of integers, find two elements whose sum is closest to zero.

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the pair of elements whose sum is closest to zero

Example:
Input:
5
1 60 -10 70 -80

Output:
-10 1

Explanation: Among all possible pairs, the sum of -10 and 1 is -9, which is the closest to zero compared to other pairs.*/ 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int arr[1000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    qsort(arr, n, sizeof(int), cmp);
    
    int left = 0;
    int right = n - 1;
    int minSum = INT_MAX;
    int result1 = arr[0], result2 = arr[n-1];
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (abs(sum) < abs(minSum)) {
            minSum = sum;
            result1 = arr[left];
            result2 = arr[right];
        }
        
        if (sum < 0) {
            left++;
        } else if (sum > 0) {
            right--;
        } else {
            break;
        }
    }
    
    if (result1 > result2) {
        int temp = result1;
        result1 = result2;
        result2 = temp;
    }
    
    printf("%d %d\n", result1, result2);
    
    return 0;
}