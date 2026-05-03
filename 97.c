/* Problem: Given meeting intervals, find minimum number of rooms required.
Sort by start time and use min-heap on end times. */


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

int compareStart(const void* a, const void* b) {
    return ((Interval*)a)->start - ((Interval*)b)->start;
}

int compareEnd(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int minMeetingRooms(Interval* intervals, int n) {
    if (n == 0) return 0;
    
    qsort(intervals, n, sizeof(Interval), compareStart);
    
    int* minHeap = (int*)malloc(n * sizeof(int));
    int heapSize = 0;
    
    minHeap[heapSize++] = intervals[0].end;
    
    for (int i = 1; i < n; i++) {
        if (intervals[i].start >= minHeap[0]) {
            minHeap[0] = intervals[i].end;
            
            int idx = 0;
            while (1) {
                int left = 2 * idx + 1;
                int right = 2 * idx + 2;
                int smallest = idx;
                
                if (left < heapSize && minHeap[left] < minHeap[smallest]) {
                    smallest = left;
                }
                if (right < heapSize && minHeap[right] < minHeap[smallest]) {
                    smallest = right;
                }
                
                if (smallest == idx) break;
                
                int temp = minHeap[idx];
                minHeap[idx] = minHeap[smallest];
                minHeap[smallest] = temp;
                idx = smallest;
            }
        } else {
            minHeap[heapSize++] = intervals[i].end;
            
            int idx = heapSize - 1;
            while (idx > 0) {
                int parent = (idx - 1) / 2;
                if (minHeap[parent] > minHeap[idx]) {
                    int temp = minHeap[parent];
                    minHeap[parent] = minHeap[idx];
                    minHeap[idx] = temp;
                    idx = parent;
                } else {
                    break;
                }
            }
        }
    }
    
    free(minHeap);
    return heapSize;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Interval* intervals = (Interval*)malloc(n * sizeof(Interval));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }
    
    int result = minMeetingRooms(intervals, n);
    printf("%d\n", result);
    
    free(intervals);
    return 0;
}
