/*Problem Statement
Given a string s consisting of lowercase letters, find the first repeated character in the string. A character is considered repeated if it appears more than once, and among all such characters, the one whose second occurrence has the smallest index should be returned.

Input Format
A single string s.

Output Format
Print the first repeated character. If no character is repeated, print -1.

Sample Input
geeksforgeeks

Sample Output
e */


#include <stdio.h>
#include <string.h>

int main() {
    char s[1000];
    scanf("%s", s);
    
    int hash[26] = {0};
    int length = strlen(s);
    int found = -1;
    
    for (int i = 0; i < length; i++) {
        int index = s[i] - 'a';
        
        if (hash[index] == 1) {
            found = i;
            break;
        }
        
        hash[index] = 1;
    }
    
    if (found != -1) {
        printf("%c\n", s[found]);
    } else {
        printf("-1\n");
    }
    
    return 0;
}
