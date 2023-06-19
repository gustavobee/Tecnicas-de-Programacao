#include <stdio.h>
#include <stdlib.h>
// Structure for a node in AVL tree
struct Node {
    int data;
    struct Node* esq;
    struct Node* right;
    int height;
};
// Function to get minimum value node in an AVL tree
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->esq != NULL) {
        current = current->esq;
    }
    return current;
}
// Function to insert a node in an AVL tree
struct Node* insert(struct Node* node, int data) {
    // Perform the normal BST insertion
    if (node == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->esq = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }
    if (data < node->data) {
        node->esq = insert(node->esq, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        // Duplicate values are not allowed in AVL tree
        return node;
    }
    // Update the height of the node
    node->height = 1 + max(getHeight(node->esq), getHeight(node->right));
    // Check if the node is balanced
    int balance = getBalance(node);
    // Perform the necessary rotations if the node is unbalanced
    if (balance > 1 && data < node->esq->data) {
        return rightRotate(node);
    }
    if (balance < -1 && data > node->right->data) {
        return leftRotate(node);
    }
    if (balance > 1 && data > node->esq->data) {
        node->esq = leftRotate(node->esq);
        return rightRotate(node);
    }
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
