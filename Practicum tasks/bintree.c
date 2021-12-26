#include <stdlib.h>
#include <stdio.h>

struct Tree {

    int data;
    struct Tree* left;
    struct Tree* right;
};


size_t tree_height(struct Tree* tree) {

    if (tree == NULL) {
        return 0;
    }

    size_t left_height = tree_height(tree->left);
    size_t right_height = tree_height(tree->right);

    if (left_height > right_height) {
        return left_height + 1;
    }

    return right_height + 1;
}


void tree_add(struct Tree** root, int data) {

    if (*root == NULL) {
        *root = (struct Tree*) malloc(sizeof(struct Tree));
        (*root)->data = data;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else if (data < (*root)->data) {
        tree_add(&(*root)->left, data);
    }
    else if (data > (*root)->data) {
        tree_add(&(*root)->right, data);
    }
}


struct Tree* tree_find(struct Tree* root, int data) {

    if (root != NULL) {
        if (data == root->data) {
            return root;
        }
        else if (data < root->data) {
            return tree_find(root->left, data);
        }
        return tree_find(root->right, data);
    }

    return NULL;
}


size_t tree_count_nodes(struct Tree* root) {

    if (root == NULL) {
        return 0;
    }

    size_t count_left = tree_count_nodes(root->left);
    size_t count_right = tree_count_nodes(root->right);

    return count_left + count_right + 1;
}


void tree_destroy(struct Tree* root) {

    if (root != NULL) {
        tree_destroy(root->left);
        tree_destroy(root->right);
        free(root);
    }
}
