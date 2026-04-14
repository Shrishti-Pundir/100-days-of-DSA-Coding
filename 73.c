/*Problem Statement
Given a string s consisting of lowercase English letters, find and return the first character that does not repeat in the string. If all characters repeat, return '$'.

Input Format
A single string s.

Output Format
Print the first non-repeating character or '$' if none exists.

Sample Input
geeksforgeeks

Sample Output
f

Explanation
The character 'f' occurs only once in the string and appears before any other non-repeating character. */


#include <stdio.h>
#include <string.h>

int main() {
    char s[1000];
    scanf("%s", s);
    
    int freq[26] = {0};
    int length = strlen(s);
    
    for (int i = 0; i < length; i++) {
        int index = s[i] - 'a';
        freq[index]++;
    }
    
    char result = '$';
    for (int i = 0; i < length; i++) {
        int index = s[i] - 'a';
        if (freq[index] == 1) {
            result = s[i];
            break;
        }
    }
    
    printf("%c\n", result);
    
    return 0;
}