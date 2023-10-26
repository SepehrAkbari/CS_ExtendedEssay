#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void leftRotate(struct Node** root) {
    struct Node* newRoot = (*root)->right;
    (*root)->right = newRoot->left;
    newRoot->left = (*root);
    *root = newRoot;
}

void rightRotate(struct Node** root) {
    struct Node* newRoot = (*root)->left;
    (*root)->left = newRoot->right;
    newRoot->right = (*root);
    *root = newRoot;
}

void splay(struct Node** root, int key) {
    if (!*root || (*root)->key == key)
        return;

    if (key < (*root)->key) {
        if (!(*root)->left)
            return;
        if (key < (*root)->left->key) {
            splay(&((*root)->left->left), key);
            rightRotate(root);
        } else if (key > (*root)->left->key) {
            splay(&((*root)->left->right), key);
            leftRotate(&((*root)->left));
        }
        if ((*root)->left)
            rightRotate(root);
    } else {
        if (!(*root)->right)
            return;
        if (key < (*root)->right->key) {
            splay(&((*root)->right->left), key);
            rightRotate(&((*root)->right));
        } else if (key > (*root)->right->key) {
            splay(&((*root)->right->right), key);
            leftRotate(root);
        }
        if ((*root)->right)
            leftRotate(root);
    }
}

void insert(struct Node** root, int key) {
    if (!*root) {
        *root = createNode(key);
        return;
    }

    splay(root, key);

    if (key < (*root)->key) {
        struct Node* newNode = createNode(key);
        newNode->left = (*root)->left;
        newNode->right = *root;
        (*root)->left = NULL;
        *root = newNode;
    } else if (key > (*root)->key) {
        struct Node* newNode = createNode(key);
        newNode->right = (*root)->right;
        newNode->left = *root;
        (*root)->right = NULL;
        *root = newNode;
    }
}

void inOrderTraversal(struct Node* root) {
    if (root) {
        inOrderTraversal(root->left);
        printf("%d ", root->key);
        inOrderTraversal(root->right);
    }
}

void freeTree(struct Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    int key;

    while (1) {
        printf("Enter a key to insert (or 'enough' to stop): ");
        char input[10];
        scanf("%s", input);

        if (strcmp(input, "enough") == 0)
            break;

        key = atoi(input);
        insert(&root, key);
    }

    printf("In-order traversal of the splay tree: ");
    inOrderTraversal(root);
    printf("\n");

    freeTree(root);
    return 0;
}
