/* Problem: Find the integer square root of a given non-negative integer using Binary Search. 
The integer square root of a number is defined as the greatest integer whose square is less than or equal to the given number.

Input:
- First line: an integer n

Output:
- Print the integer square root of n

Examples:
Input:
64

Output:
8

Input:
20

Output:
4

Input:
1

Output:
1

Explanation:
Binary Search is applied on the range 0 to n. At each step, the middle value is squared and compared with n. If mid * mid equals n, mid is the square root. 
If mid * mid is less than n, search continues in the right half; otherwise, in the left half. 
The final answer is the largest integer whose square does not exceed n. */


#include <stdio.h>

int integerSqrt(int n) {
    if (n == 0 || n == 1) {
        return n;
    }
    
    int left = 0;
    int right = n;
    int result = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if ((long long)mid * mid == n) {
            return mid;
        } else if ((long long)mid * mid < n) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int sqrt = integerSqrt(n);
    printf("%d\n", sqrt);
    
    return 0;
}
