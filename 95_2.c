/* Given an integer array nums, return the maximum difference between two successive elements in its sorted form. If the array contains less than two elements, return 0.

You must write an algorithm that runs in linear time and uses linear extra space.

 

Example 1:

Input: nums = [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.
Example 2:

Input: nums = [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
 
 */


#include <stdlib.h>
#include <limits.h>

struct Bucket {
    int min;
    int max;
    int used;
};

int maximumGap(int* nums, int numsSize) {
    if (numsSize < 2) {
        return 0;
    }
    
    int minVal = nums[0];
    int maxVal = nums[0];
    
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < minVal) minVal = nums[i];
        if (nums[i] > maxVal) maxVal = nums[i];
    }
    
    if (minVal == maxVal) {
        return 0;
    }
    
    int bucketSize = (maxVal - minVal) / (numsSize - 1);
    if (bucketSize < 1) bucketSize = 1;
    
    int bucketCount = (maxVal - minVal) / bucketSize + 1;
    
    struct Bucket* buckets = (struct Bucket*)calloc(bucketCount, sizeof(struct Bucket));
    
    for (int i = 0; i < bucketCount; i++) {
        buckets[i].min = INT_MAX;
        buckets[i].max = INT_MIN;
        buckets[i].used = 0;
    }
    
    for (int i = 0; i < numsSize; i++) {
        int idx = (nums[i] - minVal) / bucketSize;
        if (nums[i] < buckets[idx].min) buckets[idx].min = nums[i];
        if (nums[i] > buckets[idx].max) buckets[idx].max = nums[i];
        buckets[idx].used = 1;
    }
    
    int maxGap = 0;
    int prevMax = minVal;
    
    for (int i = 0; i < bucketCount; i++) {
        if (!buckets[i].used) continue;
        
        if (buckets[i].min - prevMax > maxGap) {
            maxGap = buckets[i].min - prevMax;
        }
        prevMax = buckets[i].max;
    }
    
    free(buckets);
    return maxGap;
}
