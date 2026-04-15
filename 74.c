/* Problem Statement
Given an array of candidate names where each name represents a vote cast for that candidate, determine the candidate who received the maximum number of votes. In case of a tie, return the lexicographically smallest candidate name.

Input Format
First line contains an integer n representing number of votes.
Second line contains n space-separated strings representing candidate names.

Output Format
Print the name of the winning candidate followed by the number of votes received.

Sample Input
13
john johnny jackie johnny john jackie jamie jamie john johnny jamie johnny john

Sample Output
john 4

Explanation
Both john and johnny receive 4 votes, but john is lexicographically smaller, so john is declared the winner. */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_VOTES 1000

int compare(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

int main() {
    int n;
    scanf("%d", &n);
    
    char** votes = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        votes[i] = (char*)malloc(MAX_NAME * sizeof(char));
        scanf("%s", votes[i]);
    }
    
    qsort(votes, n, sizeof(char*), compare);
    
    char winner[MAX_NAME];
    int maxVotes = 0;
    int currentVotes = 1;
    strcpy(winner, votes[0]);
    maxVotes = 1;
    
    for (int i = 1; i < n; i++) {
        if (strcmp(votes[i], votes[i - 1]) == 0) {
            currentVotes++;
        } else {
            currentVotes = 1;
        }
        
        if (currentVotes > maxVotes) {
            maxVotes = currentVotes;
            strcpy(winner, votes[i]);
        } else if (currentVotes == maxVotes) {
            if (strcmp(votes[i], winner) < 0) {
                strcpy(winner, votes[i]);
            }
        }
    }
    
    printf("%s %d\n", winner, maxVotes);
    
    for (int i = 0; i < n; i++) {
        free(votes[i]);
    }
    free(votes);
    
    return 0;
}
