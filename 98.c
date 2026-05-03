/* Problem: Given intervals, merge all overlapping ones.
Sort first, then compare with previous. */


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

int compare(const void* a, const void* b) {
    return ((Interval*)a)->start - ((Interval*)b)->start;
}

Interval* merge(Interval* intervals, int n, int* returnSize) {
    if (n == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    qsort(intervals, n, sizeof(Interval), compare);
    
    Interval* result = (Interval*)malloc(n * sizeof(Interval));
    int index = 0;
    
    result[index] = intervals[0];
    
    for (int i = 1; i < n; i++) {
        if (intervals[i].start <= result[index].end) {
            if (intervals[i].end > result[index].end) {
                result[index].end = intervals[i].end;
            }
        } else {
            index++;
            result[index] = intervals[i];
        }
    }
    
    *returnSize = index + 1;
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Interval* intervals = (Interval*)malloc(n * sizeof(Interval));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }
    
    int returnSize;
    Interval* merged = merge(intervals, n, &returnSize);
    
    for (int i = 0; i < returnSize; i++) {
        printf("%d %d", merged[i].start, merged[i].end);
        if (i < returnSize - 1) {
            printf("\n");
        }
    }
    printf("\n");
    
    free(intervals);
    free(merged);
    
    return 0;
}
