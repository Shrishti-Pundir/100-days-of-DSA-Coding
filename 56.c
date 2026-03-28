/*Problem Statement:
Check whether a given binary tree is symmetric around its center.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 indicates NULL)

Output Format:
- Print YES if symmetric, otherwise NO

Example:
Input:
7
1 2 2 3 4 4 3

Output:
YES

Explanation:
Left subtree is a mirror image of the right subtree */




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

bool isMirror(struct Node* left, struct Node* right) {
    if (left == NULL && right == NULL) {
        return true;
    }
    if (left == NULL || right == NULL) {
        return false;
    }
    
    return (left->data == right->data) && 
           isMirror(left->left, right->right) && 
           isMirror(left->right, right->left);
}

bool isSymmetric(struct Node* root) {
    if (root == NULL) {
        return true;
    }
    return isMirror(root->left, root->right);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    struct Node* root = buildTree(arr, n);
    
    if (isSymmetric(root)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    
    free(arr);
    return 0;
}