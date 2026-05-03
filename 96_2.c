/* Given an integer array nums, return the number of reverse pairs in the array.

A reverse pair is a pair (i, j) where:

0 <= i < j < nums.length and
nums[i] > 2 * nums[j].
 

Example 1:

Input: nums = [1,3,2,3,1]
Output: 2
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
Example 2:

Input: nums = [2,4,3,5,1]
Output: 3
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
(2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1
 

Constraints:

1 <= nums.length <= 5 * 104
-231 <= nums[i] <= 231 - 1 */



#include <stdlib.h>

int mergeAndCount(int* nums, int left, int mid, int right) {
    int count = 0;
    int j = mid + 1;
    
    for (int i = left; i <= mid; i++) {
        while (j <= right && (long long)nums[i] > 2 * (long long)nums[j]) {
            j++;
        }
        count += (j - (mid + 1));
    }
    
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++) L[i] = nums[left + i];
    for (int i = 0; i < n2; i++) R[i] = nums[mid + 1 + i];
    
    int i = 0, k = left;
    j = 0;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            nums[k++] = L[i++];
        } else {
            nums[k++] = R[j++];
        }
    }
    
    while (i < n1) nums[k++] = L[i++];
    while (j < n2) nums[k++] = R[j++];
    
    free(L);
    free(R);
    
    return count;
}

int mergeSortAndCount(int* nums, int left, int right) {
    int count = 0;
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        count += mergeSortAndCount(nums, left, mid);
        count += mergeSortAndCount(nums, mid + 1, right);
        count += mergeAndCount(nums, left, mid, right);
    }
    
    return count;
}

int reversePairs(int* nums, int numsSize) {
    if (numsSize < 2) return 0;
    return mergeSortAndCount(nums, 0, numsSize - 1);
}
