/*Problem: Read a string and check if it is a palindrome using two-pointer comparison.

Input:
- Single line: string s

Output:
- Print YES if palindrome, otherwise NO

Example:
Input:
level

Output:
YES

Explanation: String reads same forwards and backwards*/


#include <stdio.h>
#include <string.h>
int main() {
    char str[1000];
    scanf("%s", str);
    
    int length = strlen(str);
    int left = 0;
    int right = length - 1;
    
    while (left < right) {
        if (str[left] != str[right]) {
            printf("NO\n");
            return 0;
        }
        left++;
        right--;
    }
    
    printf("YES\n");
    return 0;
}