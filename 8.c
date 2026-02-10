#include <stdio.h>
#include <string.h>

int main() {
    char str[1000];
    scanf("%s", str);
    
    int length = strlen(str);
    int left = 0;
    int right = length - 1;
    
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
    
    printf("%s\n", str);
    return 0;
}