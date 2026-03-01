/*Problem: Circular Linked List Creation and Traversal - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the circular linked list elements starting from head, space-separated

Example:
Input:
5
10 20 30 40 50

Output:
10 20 30 40 50

Explanation:
Last node's next points to head. Traverse from head until returning to head to avoid infinite loop.*/


struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printCircular(struct Node* head, int n) {
    if (head == NULL) return;
    
    struct Node* current = head;
    for (int i = 0; i < n; i++) {
        printf("%d", current->data);
        if (i < n - 1) printf(" ");
        current = current->next;
    }
    printf("\n");
}

int main() {
    int n, value;
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        struct Node* newNode = createNode(value);
        
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    // Make it circular
    if (tail != NULL) {
        tail->next = head;
    }
    
    printCircular(head, n);
    return 0;
}
