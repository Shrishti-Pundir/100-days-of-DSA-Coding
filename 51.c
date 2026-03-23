/*Problem Statement:
Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Search Tree.

Input Format:
- First line contains integer N
- Second line contains N space-separated integers
- Third line contains two node values

Output Format:
- Print the LCA value

Example:
Input:
7
6 2 8 0 4 7 9
2 8

Output:
6*/



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

struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    
    return root;
}

struct Node* search(struct Node* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }
    
    if (value < root->data) {
        return search(root->left, value);
    }
    
    return search(root->right, value);
}

struct Node* findLCA(struct Node* root, struct Node* p, struct Node* q) {
    if (root == NULL) {
        return NULL;
    }
    
    if (p->data < root->data && q->data < root->data) {
        return findLCA(root->left, p, q);
    }
    
    if (p->data > root->data && q->data > root->data) {
        return findLCA(root->right, p, q);
    }
    
    return root;
}

int main() {
    int n, value, pVal, qVal;
    scanf("%d", &n);
    
    struct Node* root = NULL;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }
    
    scanf("%d %d", &pVal, &qVal);
    
    struct Node* p = search(root, pVal);
    struct Node* q = search(root, qVal);
    
    struct Node* lca = findLCA(root, p, q);
    
    printf("%d\n", lca->data);
    
    return 0;
}