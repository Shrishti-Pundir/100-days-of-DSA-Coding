/* Given an integer array nums and an integer k, return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, not the kth distinct element.

Can you solve it without sorting?

 

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
 

Constraints:

1 <= k <= nums.length <= 105
-104 <= nums[i] <= 104 */



#include <stdlib.h>

int partition(int* nums, int left, int right) {
    int pivot = nums[right];
    int i = left - 1;
    
    for (int j = left; j < right; j++) {
        if (nums[j] >= pivot) {
            i++;
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
    }
    
    int temp = nums[i + 1];
    nums[i + 1] = nums[right];
    nums[right] = temp;
    
    return i + 1;
}

int findKthLargest(int* nums, int numsSize, int k) {
    int freq[20001] = {0};
    int offset = 10000;
    
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i] + offset]++;
    }
    
    int count = 0;
    for (int i = 20000; i >= 0; i--) {
        if (freq[i] > 0) {
            count += freq[i];
            if (count >= k) {
                return i - offset;
            }
        }
    }
    
    return -1;
}
