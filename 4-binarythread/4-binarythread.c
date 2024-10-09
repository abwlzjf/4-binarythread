#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
    int data;
    struct tree_node* right;
    struct tree_node* left;
    int is_thread;
} TreeNode;

typedef struct thread_tree {
    TreeNode* root;
} ThreadTree;

TreeNode* new_node(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->left = newNode->right = NULL;
    newNode->data = data;
    newNode->is_thread = 0;
    return newNode;
}

TreeNode* insert_node(TreeNode* root, int data) {
    if (root == NULL) return new_node(data);
    if (data < root->data) {
        root->left = insert_node(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert_node(root->right, data);
    }
    return root;
}

TreeNode* GenerateBinaryTree(int inputData[]) {
    TreeNode* root = NULL;
    for (int i = 0; i < 15; i++) {
        root = insert_node(root, inputData[i]);
    }
    return root;
}

TreeNode* GenerateThreadTree(TreeNode* root) {
    if (root == NULL) return NULL;

    static TreeNode* prev = NULL;

    if (root->left) {
        GenerateThreadTree(root->left);
    }

    if (prev && prev->right == NULL) {
        prev->right = root;
        prev->is_thread = 1;
    }
    prev = root;

    if (root->right) {
        GenerateThreadTree(root->right);
    }

    return root;
}

void BinaryTreeInOrder(TreeNode* root) {
    if (root == NULL) return;
    BinaryTreeInOrder(root->left);
    printf("%d ", root->data);
    BinaryTreeInOrder(root->right);
}

void ThreadTreeInOrder(TreeNode* root) {
    TreeNode* current = root;

    while (current != NULL) {
        while (current->left != NULL) {
            current = current->left;
        }

        while (current != NULL) {
            printf("%d ", current->data);
            if (current->is_thread) {
                current = current->right;
            }
            else {
                current = current->right;
                break;
            }
        }
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    TreeNode* root = GenerateBinaryTree(inputData);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    TreeNode* troot = GenerateThreadTree(root);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    free(root);
    return 0;
}
