/*Problem Statement:
Given a binary tree, print its vertical order traversal. Nodes that lie on the same vertical line should be printed together from top to bottom and from left to right.

Input Format:
- First line contains integer N (number of nodes)
- Second line contains N space-separated integers representing level-order traversal (-1 indicates NULL)

Output Format:
- Print nodes column by column from leftmost to rightmost vertical line

Example:
Input:
7
1 2 3 4 5 6 7

Output:
4
2
1 5 6
3
7

Explanation:
Vertical lines are formed based on horizontal distance from root. Nodes sharing the same distance are printed together.*/




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

struct QueueNode {
    struct Node* treeNode;
    int hd;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

void enqueue(struct Queue* q, struct Node* node, int hd) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = node;
    newNode->hd = hd;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

struct QueueNode* dequeue(struct Queue* q) {
    if (q->front == NULL) return NULL;
    
    struct QueueNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return temp;
}

void verticalOrder(struct Node* root) {
    if (root == NULL) return;
    
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;
    
    struct Node** map = (struct Node**)malloc(sizeof(struct Node*) * 2000);
    int minHD = 0, maxHD = 0;
    
    enqueue(q, root, 1000);
    
    while (q->front != NULL) {
        struct QueueNode* current = dequeue(q);
        struct Node* node = current->treeNode;
        int hd = current->hd;
        
        if (map[hd] == NULL) {
            map[hd] = (struct Node*)malloc(sizeof(struct Node));
            map[hd]->data = node->data;
            map[hd]->next = NULL;
        } else {
            struct Node* temp = map[hd];
            while (temp->next != NULL) {
                temp = temp->next;
            }
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->data = node->data;
            newNode->next = NULL;
            temp->next = newNode;
        }
        
        if (hd < minHD) minHD = hd;
        if (hd > maxHD) maxHD = hd;
        
        if (node->left != NULL) {
            enqueue(q, node->left, hd - 1);
        }
        if (node->right != NULL) {
            enqueue(q, node->right, hd + 1);
        }
        
        free(current);
    }
    
    for (int i = minHD; i <= maxHD; i++) {
        if (map[i] != NULL) {
            struct Node* temp = map[i];
            while (temp != NULL) {
                printf("%d", temp->data);
                if (temp->next != NULL) {
                    printf(" ");
                }
                temp = temp->next;
            }
            printf("\n");
        }
    }
    
    free(q);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    struct Node* root = buildTree(arr, n);
    verticalOrder(root);
    
    free(arr);
    return 0;
}