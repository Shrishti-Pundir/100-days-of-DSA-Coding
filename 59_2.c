/*Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.

 

Example 1:


Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: inorder = [-1], postorder = [-1]
Output: [-1] */




struct TreeNode* build(int* inorder, int inStart, int inEnd, int* postorder, int postStart, int postEnd) {
    if (inStart > inEnd || postStart > postEnd) {
        return NULL;
    }
    
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = postorder[postEnd];
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
    
    root->left = build(inorder, inStart, rootIndex - 1, postorder, postStart, postStart + leftSize - 1);
    root->right = build(inorder, rootIndex + 1, inEnd, postorder, postStart + leftSize, postEnd - 1);
    
    return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    return build(inorder, 0, inorderSize - 1, postorder, 0, postorderSize - 1);
}