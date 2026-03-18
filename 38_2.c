/*You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

 

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]*/



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc(sizeof(int) * (*returnSize));
    int* deque = (int*)malloc(sizeof(int) * numsSize); // store indices
    int front = 0, rear = -1;
    int resIdx = 0;
    
    for (int i = 0; i < numsSize; i++) {
        // Remove indices out of current window
        if (front <= rear && deque[front] <= i - k) {
            front++;
        }
        
        // Remove from rear while current element is greater than elements at those indices
        while (front <= rear && nums[deque[rear]] <= nums[i]) {
            rear--;
        }
        
        // Add current index to deque
        deque[++rear] = i;
        
        // If window has reached size k, add max to result
        if (i >= k - 1) {
            result[resIdx++] = nums[deque[front]];
        }
    }
    
    free(deque);
    return result;
}
