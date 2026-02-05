/*Problem: A system receives two separate logs of user arrival times from two different servers. 
Each log is already sorted in ascending order. Your task is to create a single chronological log,
that preserves the correct order of arrivals.

Input:
- First line: integer p (number of entries in server log 1)
- Second line: p sorted integers representing arrival times from server 1
- Third line: integer q (number of entries in server log 2)
- Fourth line: q sorted integers representing arrival times from server 2)

Output:
- Print a single line containing all arrival times in chronological order, separated by spaces

Example:
Input:
5
10 20 30 50 70
4
15 25 40 60

Output:
10 15 20 25 30 40 50 60 70

Explanation: Compare the next unprocessed arrival time from both logs,
and append the earlier one to the final log until all entries are processed*/


#include<stdio.h>
int main(){
    
    int p, q, log1[50], log2[50];
    int i = 0, j = 0;

    printf("Enter the number of entries in server log 1= ");
    scanf("%d", &p);
    printf("Enter the elements of server 1 = ");
    for(i = 0; i < p; i++){
        scanf("%d", &log1[i]);
    }

    printf("Enter the number of entries in server log 2= ");
    scanf("%d", &q);
    printf("Enter the elements of server 2 = ");
    for(i = 0; i < q; i++){
        scanf("%d", &log2[i]);
    }
    
    // RESET i to 0 for merging!
    i = 0;
    
    while(i < p && j < q){
        if(log1[i] <= log2[j]){
            printf("%d ", log1[i]);
            i++;
        }else{
            printf("%d ", log2[j]);
            j++;
        }
    }

    while(i < p){
        printf("%d ", log1[i]);
        i++;
    }

    while(j < q){
        printf("%d ", log2[j]);
        j++;
    }

    return 0;
}