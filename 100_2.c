/* Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].

 

Example 1:

Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Example 2:

Input: nums = [-1]
Output: [0]
Example 3:

Input: nums = [-1,-1]
Output: [0,0]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104 */



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct {
    int val;
    int index;
    int count;
} Element;

void merge(Element* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    Element* L = (Element*)malloc(n1 * sizeof(Element));
    Element* R = (Element*)malloc(n2 * sizeof(Element));
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    int smallerCount = 0;
    
    while (i < n1 && j < n2) {
        if (L[i].val <= R[j].val) {
            arr[k] = L[i];
            arr[k].count += smallerCount;
            i++;
        } else {
            arr[k] = R[j];
            smallerCount++;
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        arr[k].count += smallerCount;
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void mergeSort(Element* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    Element* elements = (Element*)malloc(numsSize * sizeof(Element));
    
    for (int i = 0; i < numsSize; i++) {
        elements[i].val = nums[i];
        elements[i].index = i;
        elements[i].count = 0;
    }
    
    mergeSort(elements, 0, numsSize - 1);
    
    int* result = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        result[elements[i].index] = elements[i].count;
    }
    
    free(elements);
    *returnSize = numsSize;
    return result;
}
