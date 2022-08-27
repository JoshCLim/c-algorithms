#include <stdlib.h>
#include <stdbool.h>

#include "Tree.h"

// ! copied over from Tree.c
typedef struct Node {
    Item data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

// ---- function prototypes ---- //
bool check_balanced(Tree);
int left_height(Tree);
int right_height(Tree);

bool check_balanced(Tree t) {
    if (t == NULL) {
        return true;
    }
    if (!check_balanced(t->left)) {
        return false;
    }
    if (!check_balanced(t->right)) {
        return false;
    }
    
    int balance = left_height(t) - right_height(t);
    if (balance < -1 || balance > 1) {
        return false;
    }

    return true;
}

// ---- helper functions ---- //
int left_height(Tree t) {
    if (t == NULL) {
        return 0;
    }
    if (t->left == NULL) {
        return 0;
    }

    return t->left->height;
}

int right_height(Tree t) {
    if (t == NULL) {
        return 0;
    }
    if (t->right == NULL) {
        return 0;
    }

    return t->right->height;
}
