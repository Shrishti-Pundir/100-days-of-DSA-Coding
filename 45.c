/*Problem Statement:
Find the height (maximum depth) of a given binary tree.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 represents NULL)

Output Format:
- Print the height of the tree

Example:
Input:
7
1 2 3 4 5 -1 -1

Output:
3
*/



#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* buildTree(int* arr, int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    
    struct Node* root = createNode(arr[0]);
    struct Node** queue = (struct Node**)malloc(sizeof(struct Node*) * n);
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    int i = 1;
    while (i < n && front < rear) {
        struct Node* current = queue[front++];
        
        if (i < n && arr[i] != -1) {
            current->left = createNode(arr[i]);
            queue[rear++] = current->left;
        }
        i++;
        
        if (i < n && arr[i] != -1) {
            current->right = createNode(arr[i]);
            queue[rear++] = current->right;
        }
        i++;
    }
    
    free(queue);
    return root;
}

int maxDepth(struct Node* root) {
    if (root == NULL) return 0;
    
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);
    
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    struct Node* root = buildTree(arr, n);
    int height = maxDepth(root);
    printf("%d\n", height);
    
    free(arr);
    return 0;
}
