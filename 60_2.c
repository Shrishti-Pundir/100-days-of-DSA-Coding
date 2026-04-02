/*You are given the root of a binary tree. We install cameras on the tree nodes where each camera at a node can monitor its parent, itself, and its immediate children.

Return the minimum number of cameras needed to monitor all nodes of the tree.

 

Example 1:


Input: root = [0,0,null,0,0]
Output: 1
Explanation: One camera is enough to monitor all nodes if placed as shown.
Example 2:


Input: root = [0,0,null,0,null,0,null,null,0]
Output: 2
Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of the valid configurations of camera placement. */




int cameras;

int dfs(struct TreeNode* node) {
    if (node == NULL) {
        return 1;
    }
    
    int left = dfs(node->left);
    int right = dfs(node->right);
    
    if (left == 0 || right == 0) {
        cameras++;
        return 2;
    }
    
    if (left == 2 || right == 2) {
        return 1;
    }
    
    return 0;
}

int minCameraCover(struct TreeNode* root) {
    cameras = 0;
    
    int result = dfs(root);
    
    if (result == 0) {
        cameras++;
    }
    
    return cameras;
}