/*Problem Statement:
Construct a binary tree from given inorder and postorder traversal arrays.

Input Format:
- First line contains integer N
- Second line contains inorder traversal
- Third line contains postorder traversal

Output Format:
- Print preorder traversal of constructed tree

Example:
Input:
5
4 2 5 1 3
4 5 2 3 1

Output:
1 2 4 5 3

Explanation:
Postorder gives root at end, inorder divides left and right subtrees. */




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

int search(int* inorder, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value) {
            return i;
        }
    }
    return -1;
}

struct Node* buildTree(int* inorder, int* postorder, int inStart, int inEnd, int postStart, int postEnd) {
    if (inStart > inEnd || postStart > postEnd) {
        return NULL;
    }
    
    struct Node* root = createNode(postorder[postEnd]);
    
    int rootIndex = search(inorder, inStart, inEnd, root->data);
    int leftSize = rootIndex - inStart;
    
    root->left = buildTree(inorder, postorder, inStart, rootIndex - 1, postStart, postStart + leftSize - 1);
    root->right = buildTree(inorder, postorder, rootIndex + 1, inEnd, postStart + leftSize, postEnd - 1);
    
    return root;
}

void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* inorder = (int*)malloc(sizeof(int) * n);
    int* postorder = (int*)malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &postorder[i]);
    }
    
    struct Node* root = buildTree(inorder, postorder, 0, n - 1, 0, n - 1);
    preorder(root);
    printf("\n");
    
    free(inorder);
    free(postorder);
    return 0;
}