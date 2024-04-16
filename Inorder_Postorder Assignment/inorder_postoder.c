#include <stdio.h>
#include <stdlib.h>

// Define the structure for a BST node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to construct the BST from in-order and post-order arrays
struct Node* bst_construct(int in[], int post[], int inStart, int inEnd, int* postIndex) {
    // Base case: if the in-order array has no elements
    if (inStart > inEnd) {
        return NULL;
    }

    // Get the current root data from post-order array using postIndex
    int rootData = post[*postIndex];
    struct Node* root = createNode(rootData);
    (*postIndex)--;

    // Find the index of the root data in in-order array
    int rootIndex;
    for (rootIndex = inStart; rootIndex <= inEnd; rootIndex++) {
        if (in[rootIndex] == rootData) {
            break;
        }
    }

    // Recursively construct the right and left subtrees
    // Right subtree is constructed before the left subtree because of post-order
    root->right = bst_construct(in, post, rootIndex + 1, inEnd, postIndex);
    root->left = bst_construct(in, post, inStart, rootIndex - 1, postIndex);

    return root;
}

// Define a queue structure for BFS traversal
struct QueueNode {
    struct Node* treeNode;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Function to create a new queue node
struct QueueNode* createQueueNode(struct Node* treeNode) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue a tree node
void enqueue(struct Queue* queue, struct Node* treeNode) {
    struct QueueNode* newNode = createQueueNode(treeNode);
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue a tree node
struct Node* dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }
    struct QueueNode* temp = queue->front;
    struct Node* treeNode = temp->treeNode;
    queue->front = queue->front->next;
    free(temp);
    return treeNode;
}

// Function for BFS traversal and printing each element
void bfs_traversal(struct Node* root) {
    if (root == NULL) {
        return;
    }

    // Create a queue for BFS traversal
    struct Queue* queue = createQueue();

    // Enqueue the root node
    enqueue(queue, root);

    // Perform BFS traversal
    while (!isEmpty(queue)) {
        struct Node* currentNode = dequeue(queue);
        printf("%d ", currentNode->data);

        // Enqueue left and right children if they exist
        if (currentNode->left != NULL) {
            enqueue(queue, currentNode->left);
        }
        if (currentNode->right != NULL) {
            enqueue(queue, currentNode->right);
        }
    }

    // Clean up the queue
    free(queue);
}

// Function to print an array in the desired format
void print_array(int arr[], int length, const char* prefix, const char* separator) {
    printf("%s", prefix);
    for (int i = 0; i < length; i++) {
        printf("%d", arr[i]);
        if (i < length - 1) {
            printf("%s", separator);
        }
    }
    printf("\n");
}

int main() {
    // Given in-order and post-order traversal arrays
    int in_order[] = {5, 10, 15, 20, 25, 30, 45};
    int post_order[] = {5, 15, 10, 25, 45, 30, 20};

    // Calculate the length of the arrays
    int n = sizeof(in_order) / sizeof(in_order[0]);

    // Print arrays as specified in the requirements
    print_array(post_order, n, "Post-order: ", " ");
    print_array(in_order, n, "\nIn-order: ", ", ");

    // Index for post_order traversal, start at the last element
    int postIndex = n - 1;

    // Construct the BST using in-order and post-order arrays
    struct Node* root = bst_construct(in_order, post_order, 0, n - 1, &postIndex);

    // Perform BFS traversal and print each element
    printf("\nBFS traversal: ");
    bfs_traversal(root);
    printf("\n");

    return 0;
}
