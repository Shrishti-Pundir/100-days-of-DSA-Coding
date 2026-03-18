/* Problem: Level Order Traversal

Implement the solution for this problem.

Input:
- Input specifications

Output:
- Output specifications */


#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* buildTree(int* arr, int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    
    struct TreeNode* root = createNode(arr[0]);
    struct TreeNode** queue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * n);
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    int i = 1;
    while (i < n && front < rear) {
        struct TreeNode* current = queue[front++];
        
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

void levelOrder(struct TreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    struct TreeNode** queue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 1000);
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    printf("Level Order Traversal:\n");
    
    while (front < rear) {
        int levelSize = rear - front;
        
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            printf("%d ", node->val);
            
            if (node->left != NULL) {
                queue[rear++] = node->left;
            }
            if (node->right != NULL) {
                queue[rear++] = node->right;
            }
        }
        printf("\n");
    }
    
    free(queue);
}

int main() {
    int n;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(sizeof(int) * n);
    printf("Enter level order traversal (-1 for NULL):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    struct TreeNode* root = buildTree(arr, n);
    levelOrder(root);
    
    free(arr);
    return 0;
}
