/* Problem: Given a target distance and cars’ positions & speeds, compute the number of car fleets reaching the destination.
Sort cars by position in descending order and calculate time to reach target. */



#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int position;
    int speed;
} Car;

int compare(const void* a, const void* b) {
    return ((Car*)b)->position - ((Car*)a)->position;
}

int carFleet(int target, int* position, int* speed, int n) {
    if (n == 0) return 0;
    
    Car* cars = (Car*)malloc(n * sizeof(Car));
    for (int i = 0; i < n; i++) {
        cars[i].position = position[i];
        cars[i].speed = speed[i];
    }
    
    qsort(cars, n, sizeof(Car), compare);
    
    double* time = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        time[i] = (double)(target - cars[i].position) / cars[i].speed;
    }
    
    int fleets = 1;
    double maxTime = time[0];
    
    for (int i = 1; i < n; i++) {
        if (time[i] > maxTime) {
            fleets++;
            maxTime = time[i];
        }
    }
    
    free(cars);
    free(time);
    
    return fleets;
}

int main() {
    int target, n;
    scanf("%d %d", &target, &n);
    
    int* position = (int*)malloc(n * sizeof(int));
    int* speed = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &position[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &speed[i]);
    }
    
    int result = carFleet(target, position, speed, n);
    printf("%d\n", result);
    
    free(position);
    free(speed);
    
    return 0;
}
