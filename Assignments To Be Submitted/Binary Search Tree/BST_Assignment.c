#include <stdio.h>
#include <stdlib.h>

// Structure for a BST Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a node into the BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to find the height of the BST
int height(struct Node* root) {
    if (root == NULL)
        return -1; // Height of an empty tree is -1
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        // Height of the tree is maximum of left and right subtrees plus 1
        if (leftHeight > rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
    }
}

// Function to print the level and height of a node
void printLevelAndHeight(struct Node* root, int key, int level) {
    if (root == NULL) {
        printf("Node not found.\n");
        return;
    }
    if (root->data == key) {
        printf("Level of node %d: %d\n\n", key, level);
        printf("Height of node %d: %d\n\n", key, height(root));
        return;
    }
    if (key < root->data)
        printLevelAndHeight(root->left, key, level + 1);
    else
        printLevelAndHeight(root->right, key, level + 1);
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = NULL;

    // displaying the nodes
    printf("Array values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // Creating the BST
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    // Deleting a node
    int keyToDelete = 20;
    root = deleteNode(root, keyToDelete);
    printf("Node %d deleted from the BST.\n\n", keyToDelete);

    // Find the index of node 20 in the array
    int indexToDelete = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 20) {
            indexToDelete = i;
            break;
        }
    }

    // If node 20 is found, delete it from the array
    if (indexToDelete != -1) {
        for (int i = indexToDelete; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }
        n--; // Decrease the size of the array
    }

    // Display the updated array
    printf("Array values after deleting node 20: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // Printing the height of the BST
    printf("Height of the BST: %d\n\n", height(root));

    // Printing the level and height of a specified node
    int nodeToFind = 30;
    printLevelAndHeight(root, nodeToFind, 0);

    return 0;
}
