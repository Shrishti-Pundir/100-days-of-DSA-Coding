/*Problem Statement:
Construct a binary tree from given preorder and inorder traversal arrays.

Input Format:
- First line contains integer N
- Second line contains preorder traversal
- Third line contains inorder traversal

Output Format:
- Print postorder traversal of constructed tree

Example:
Input:
5
1 2 4 5 3
4 2 5 1 3

Output:
4 5 2 3 1

Explanation:
Preorder identifies root, inorder splits left and right subtrees*/




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

struct Node* buildTree(int* preorder, int* inorder, int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) {
        return NULL;
    }
    
    struct Node* root = createNode(preorder[preStart]);
    
    int rootIndex = search(inorder, inStart, inEnd, root->data);
    int leftSize = rootIndex - inStart;
    
    root->left = buildTree(preorder, inorder, preStart + 1, preStart + leftSize, inStart, rootIndex - 1);
    root->right = buildTree(preorder, inorder, preStart + leftSize + 1, preEnd, rootIndex + 1, inEnd);
    
    return root;
}

void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* preorder = (int*)malloc(sizeof(int) * n);
    int* inorder = (int*)malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }
    
    struct Node* root = buildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    postorder(root);
    printf("\n");
    
    free(preorder);
    free(inorder);
    return 0;
}