/*Problem Statement:
Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Tree.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 represents NULL)
- Third line contains two node values

Output Format:
- Print the LCA value

Example:
Input:
7
1 2 3 4 5 6 7
4 5

Output:
2 */



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

struct Node* findNode(struct Node* root, int value) {
    if (root == NULL) return NULL;
    if (root->data == value) return root;
    
    struct Node* left = findNode(root->left, value);
    if (left != NULL) return left;
    
    return findNode(root->right, value);
}

struct Node* findLCA(struct Node* root, struct Node* p, struct Node* q) {
    if (root == NULL || root == p || root == q) {
        return root;
    }
    
    struct Node* left = findLCA(root->left, p, q);
    struct Node* right = findLCA(root->right, p, q);
    
    if (left != NULL && right != NULL) {
        return root;
    }
    
    return (left != NULL) ? left : right;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int pVal, qVal;
    scanf("%d %d", &pVal, &qVal);
    
    struct Node* root = buildTree(arr, n);
    struct Node* p = findNode(root, pVal);
    struct Node* q = findNode(root, qVal);
    
    struct Node* lca = findLCA(root, p, q);
    
    printf("%d\n", lca->data);
    
    free(arr);
    return 0;
}