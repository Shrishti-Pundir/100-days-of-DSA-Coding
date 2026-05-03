/* Problem: For each element, count how many smaller elements appear on right side.
Use merge sort technique or Fenwick Tree (BIT). */ 


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int index;
    int count;
} Element;

void merge(Element arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    Element* L = (Element*)malloc(n1 * sizeof(Element));
    Element* R = (Element*)malloc(n2 * sizeof(Element));
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
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

void mergeSort(Element arr[], int left, int right) {
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

int main() {
    int n;
    scanf("%d", &n);
    
    int* nums = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    
    int returnSize;
    int* result = countSmaller(nums, n, &returnSize);
    
    for (int i = 0; i < returnSize; i++) {
        printf("%d", result[i]);
        if (i < returnSize - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(nums);
    free(result);
    
    return 0;
}
