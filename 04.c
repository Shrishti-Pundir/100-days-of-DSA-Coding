/*Problem: Given an array of n integers, reverse the array in-place using two-pointer approach.

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the reversed array, space-separated

Example:
Input:
5
1 2 3 4 5

Output:
5 4 3 2 1

Explanation: Swap pairs from both ends: (1,5), (2,4), middle 3 stays*/
  
#include <stdio.h>

int main()
{
   int n;
   scanf("%d", &n);
   int a[n];
   for (int i = 0; i < n; i++) 
       scanf("%d", &a[i]);
   
   int left = 0;
   int right = n - 1;
   
   while (left < right)
   {
       int temp = a[left];
       a[left] = a[right];
       a[right] = temp;
       
       left++;
       right--;
   }
   
   for (int i = 0; i < n; i++)
       printf("%d ", a[i]);
   
   return 0;

}
