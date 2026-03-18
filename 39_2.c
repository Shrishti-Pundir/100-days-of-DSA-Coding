/*Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

 

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2

Output: [1,2]

Example 2:

Input: nums = [1], k = 1

Output: [1]

Example 3:

Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2

Output: [1,2]

*/

typedef struct {
    int num;
    int freq;
} Element;

int compareFreq(const void* a, const void* b) {
    return ((Element*)b)->freq - ((Element*)a)->freq;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    Element* elements = (Element*)malloc(sizeof(Element) * numsSize);
    int uniqueCount = 0;
    
    for (int i = 0; i < numsSize; i++) {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (elements[j].num == nums[i]) {
                elements[j].freq++;
                found = 1;
                break;
            }
        }
        if (!found) {
            elements[uniqueCount].num = nums[i];
            elements[uniqueCount].freq = 1;
            uniqueCount++;
        }
    }
    
    qsort(elements, uniqueCount, sizeof(Element), compareFreq);
    
    *returnSize = k;
    int* result = (int*)malloc(sizeof(int) * k);
    
    for (int i = 0; i < k; i++) {
        result[i] = elements[i].num;
    }
    
    free(elements);
    return result;
}
