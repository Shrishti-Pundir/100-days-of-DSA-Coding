/*Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

 

Example 1:

Input: root = [1,2,3,null,5,null,4]

Output: [1,3,4]

Explanation:



Example 2:

Input: root = [1,2,3,4,null,null,null,5]

Output: [1,3,4,5]

Explanation:



Example 3:

Input: root = [1,null,3]

Output: [1,3]

Example 4:

Input: root = []

Output: []  */



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    
    int* result = (int*)malloc(sizeof(int) * 1000);
    *returnSize = 0;
    
    struct TreeNode** queue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 1000);
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    while (front < rear) {
        int levelSize = rear - front;
        
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            
            if (i == levelSize - 1) {
                result[(*returnSize)++] = node->val;
            }
            
            if (node->left != NULL) {
                queue[rear++] = node->left;
            }
            if (node->right != NULL) {
                queue[rear++] = node->right;
            }
        }
    }
    
    free(queue);
    return result;
}