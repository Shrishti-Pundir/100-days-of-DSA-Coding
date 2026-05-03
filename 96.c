/* Problem: Count number of inversions using modified merge sort.
Inversion if i < j and a[i] > a[j]. */


#include <stdio.h>
#include <stdlib.h>

long long mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    long long invCount = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1);
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
    
    return invCount;
}

long long mergeSortAndCount(int arr[], int temp[], int left, int right) {
    long long invCount = 0;
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        invCount += mergeSortAndCount(arr, temp, left, mid);
        invCount += mergeSortAndCount(arr, temp, mid + 1, right);
        invCount += mergeAndCount(arr, temp, left, mid, right);
    }
    
    return invCount;
}

long long countInversions(int arr[], int n) {
    int* temp = (int*)malloc(n * sizeof(int));
    long long invCount = mergeSortAndCount(arr, temp, 0, n - 1);
    free(temp);
    return invCount;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int arr[100000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    long long inversions = countInversions(arr, n);
    printf("%lld\n", inversions);
    
    return 0;
}
