/*Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "3+2*2"
Output: 7
Example 2:

Input: s = " 3/2 "
Output: 1
Example 3:

Input: s = " 3+5 / 2 "
Output: 5*/


int calculate(char* s) {
    int stack[300000];
    int top = -1;
    int currentNum = 0;
    char lastOp = '+';
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            currentNum = currentNum * 10 + (s[i] - '0');
        }
        
        if ((s[i] < '0' || s[i] > '9') && s[i] != ' ' || s[i+1] == '\0') {
            if (lastOp == '+') {
                stack[++top] = currentNum;
            } else if (lastOp == '-') {
                stack[++top] = -currentNum;
            } else if (lastOp == '*') {
                stack[top] = stack[top] * currentNum;
            } else if (lastOp == '/') {
                stack[top] = stack[top] / currentNum;
            }
            
            currentNum = 0;
            lastOp = s[i];
        }
    }
    
    int result = 0;
    while (top >= 0) {
        result += stack[top--];
    }
    
    return result;
}
