/*Given a 2D integer array matrix, return the transpose of matrix.

The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.



 

Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]
Example 2:

Input: matrix = [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]
*/


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) {
    int m = matrixSize;
    int n = matrixColSize[0];
    
    *returnSize = n;
    
    *returnColumnSizes = (int*)malloc(sizeof(int) * n);
    
    int** result = (int**)malloc(sizeof(int*) * n);
    
    for (int i = 0; i < n; i++) {
        result[i] = (int*)malloc(sizeof(int) * m);
        (*returnColumnSizes)[i] = m;
        
        for (int j = 0; j < m; j++) {
            result[i][j] = matrix[j][i];
        }
    }
    
    return result;
}
