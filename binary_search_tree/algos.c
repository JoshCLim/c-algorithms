#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "algos.h"

// prototypes
static int max(Item one, Item two);

// checks if a tree is a valid binary search tree
bool tree_validate(Tree t) {
    if (t == NULL) {
        return true;
    }
    if (t->left != NULL && t->data <= t->left->data) {
        return false;
    }
    if (t->right != NULL && t->data >= t->right->data) {
        return false;
    }
    return tree_validate(t->left) && tree_validate(t->right);
}

// returns number of nodes in a Tree
int tree_num_nodes(Tree t) {
    if (t == NULL) {
        return 0;
    }
    return tree_num_nodes(t->left) + tree_num_nodes(t->right) + 1;
}

// returns height of the tree
int tree_height(Tree t) {
    if (t == NULL) {
        return 0;
    }
    return max(tree_height(t->left), tree_height(t->right)) + 1;
}

// // rotate a node left/right
// Tree tree_rotate_right(Tree);
// Tree tree_rotate_left(Tree);

// // insert a value at the tree's root
// Tree tree_insert_at_root(Tree, Item);

// traversals
void tree_print_inorder(Tree t) {
    if (t == NULL) {
        return;
    }
    tree_print_inorder(t->left);
    printf("%d, ", t->data);
    tree_print_inorder(t->right);
}
void tree_print_preorder(Tree t) {
    if (t == NULL) {
        return;
    }
    printf("%d, ", t->data);
    tree_print_preorder(t->left);
    tree_print_preorder(t->right);
}
void tree_print_postorder(Tree t) {
    if (t == NULL) {
        return;
    }
    tree_print_postorder(t->left);
    tree_print_postorder(t->right);
    printf("%d, ", t->data);
}
void tree_print_levelorder(Tree t) {}

// helper functions
static int max(Item one, Item two) {
    return one > two ? one : two;
}