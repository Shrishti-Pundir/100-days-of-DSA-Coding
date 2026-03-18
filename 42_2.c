/*The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.
 
Example 1:

Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
 

Constraints:

-105 <= num <= 105
There will be at least one element in the data structure before calling findMedian.
At most 5 * 104 calls will be made to addNum and findMedian.
 

Follow up:

If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?*/


#include <stdlib.h>

/* Heap structure */
typedef struct {
    int* arr;
    int size;
    int capacity;
    int isMinHeap;
} Heap;

/* MedianFinder */
typedef struct {
    Heap* left;
    Heap* right;
} MedianFinder;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

Heap* createHeap(int capacity, int isMinHeap) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->capacity = capacity;
    h->size = 0;
    h->isMinHeap = isMinHeap;
    h->arr = (int*)malloc(sizeof(int) * capacity);
    return h;
}

void ensureCapacity(Heap* h) {
    if (h->size < h->capacity) return;
    h->capacity *= 2;
    h->arr = (int*)realloc(h->arr, sizeof(int) * h->capacity);
}

int compare(Heap* h, int a, int b) {
    return h->isMinHeap ? a < b : a > b;
}

void heapifyUp(Heap* h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (compare(h, h->arr[i], h->arr[p])) {
            swap(&h->arr[i], &h->arr[p]);
            i = p;
        } else break;
    }
}

void heapifyDown(Heap* h, int i) {
    while (1) {
        int l = 2*i + 1, r = 2*i + 2, best = i;
        if (l < h->size && compare(h, h->arr[l], h->arr[best])) best = l;
        if (r < h->size && compare(h, h->arr[r], h->arr[best])) best = r;
        if (best != i) {
            swap(&h->arr[i], &h->arr[best]);
            i = best;
        } else break;
    }
}

void heapPush(Heap* h, int val) {
    ensureCapacity(h);
    h->arr[h->size] = val;
    heapifyUp(h, h->size);
    h->size++;
}

int heapPop(Heap* h) {
    int top = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heapifyDown(h, 0);
    return top;
}

int heapTop(Heap* h) {
    return h->arr[0];
}

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->left = createHeap(16, 0);
    obj->right = createHeap(16, 1);
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if (obj->left->size == 0 || num <= heapTop(obj->left))
        heapPush(obj->left, num);
    else
        heapPush(obj->right, num);

    if (obj->left->size > obj->right->size + 1)
        heapPush(obj->right, heapPop(obj->left));
    else if (obj->right->size > obj->left->size)
        heapPush(obj->left, heapPop(obj->right));
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->left->size > obj->right->size)
        return heapTop(obj->left);
    return (heapTop(obj->left) + heapTop(obj->right)) / 2.0;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->left->arr);
    free(obj->right->arr);
    free(obj->left);
    free(obj->right);
    free(obj);
}
