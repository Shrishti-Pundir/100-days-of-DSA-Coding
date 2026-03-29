/* Problem Statement:
Convert a binary tree into its mirror image by swapping left and right children at every node.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 indicates NULL)

Output Format:
- Print inorder traversal of mirrored tree

Example:
Input:
7
1 2 3 4 5 6 7

Output:
7 3 6 1 5 2 4

Explanation:
Each node’s left and right children are swapped recursively.  */



#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Build binary tree from level-order input (-1 for NULL)
struct TreeNode* buildTree(int* arr, int n, int* index) {
    if (*index >= n || arr[*index] == -1) {
        (*index)++;
        return NULL;
    }
    
    struct TreeNode* root = newNode(arr[*index]);
    (*index)++;
    
    root->left = buildTree(arr, n, index);
    root->right = buildTree(arr, n, index);
    
    return root;
}

// Mirror the tree by swapping left and right children recursively
void mirror(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    
    // Swap left and right
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    // Recur for subtrees
    mirror(root->left);
    mirror(root->right);
}

// Inorder traversal: Left -> Root -> Right
void inorder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

int main() {
    int N;
    scanf("%d", &N);
    
    int* arr = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    
    int index = 0;
    struct TreeNode* root = buildTree(arr, N, &index);
    
    // Convert to mirror tree
    mirror(root);
    
    // Print inorder traversal of mirrored tree
    inorder(root);
    printf("\n");
    
    // Free memory (optional for most judges)
    // You can add a proper free function if needed
    
    free(arr);
    return 0;
}