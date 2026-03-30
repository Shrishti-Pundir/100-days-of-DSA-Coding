/*Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

 

Example 1:


Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: preorder = [-1], inorder = [-1]
Output: [-1]*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* build(int* preorder, int preStart, int preEnd, int* inorder, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) {
        return NULL;
    }
    
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = preorder[preStart];
    root->left = NULL;
    root->right = NULL;
    
    int rootIndex;
    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == root->val) {
            rootIndex = i;
            break;
        }
    }
    
    int leftSize = rootIndex - inStart;
    
    root->left = build(preorder, preStart + 1, preStart + leftSize, inorder, inStart, rootIndex - 1);
    root->right = build(preorder, preStart + leftSize + 1, preEnd, inorder, rootIndex + 1, inEnd);
    
    return root;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    return build(preorder, 0, preorderSize - 1, inorder, 0, inorderSize - 1);
}