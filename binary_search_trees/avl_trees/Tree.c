#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tree.h"
#include "logs/log.h"

#define MAX_LEN 100

char buffer[MAX_LEN];

typedef struct Node {
    Item data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

// ---- function prototypes ---- //
Tree tree_create(Item);
Tree tree_delete(Tree);
Tree tree_insert(Tree, Item);
Tree tree_remove(Tree, Item);
bool tree_search(Tree, Item);
void tree_show(Tree);
void tree_show_formatted(Tree, int);
void tree_list(Tree);
void tree_list_formatted(Tree);
void tree_info(Tree);
void tree_info_formatted(Tree, int);
Tree delete_node(Tree);
Item find_min_value(Tree);
Tree rotate_right(Tree);
Tree rotate_left(Tree);
int calculate_height(Tree);
int max(int, int);

// ---- interface functions ---- //
Tree tree_create(Item item) {
    Tree new_node = (Tree) malloc(sizeof(Node));
    new_node->data = item;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 0;

    snprintf(buffer, MAX_LEN, "\n|------------------|\n");
    log_output(buffer);
    snprintf(buffer, MAX_LEN, "new AVL tree created with item %d\n", item);
    log_output(buffer);

    return new_node;
}

Tree tree_delete(Tree t) {
    if (t != NULL) {
        tree_delete(t->left);
        tree_delete(t->right);
        free(t);
    }
    return NULL;
}

Tree tree_insert(Tree t, Item item) {
    if (t == NULL) { // if curr value == NULL, insert here
        Tree new_node = (Tree) malloc(sizeof(Node));
        new_node->data = item;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height = 1;

        t = new_node;

        snprintf(buffer, MAX_LEN, "\ninserting %d\n", t->data);
        log_output(buffer);

        return t;

    } else if (item == t->data) {
        return t;
    }

    if (item < t->data) { // else if curr value bigger than value, go left (and repeat/recurse)
        t->left = tree_insert(t->left, item);
        // t->height = t->left->height + 1;
    } else if (item > t->data) { // else if curr value smaller than value, go right (and repeat/recurse)
        t->right = tree_insert(t->right, item);
        // t->height = t->right->height + 1;
    }

    t->height = calculate_height(t);

    int l_height = 0;
    if (t->left != NULL) {
        l_height = t->left->height;
    }
    int r_height = 0;
    if (t->right != NULL) {
        r_height = t->right->height;
    }

    snprintf(
        buffer, 
        MAX_LEN, 
        "    data=%d, height=%d, l_height=%d, r_height=%d\n", 
        t->data, t->height, l_height, r_height
    );
    log_output(buffer);

    if (l_height - r_height > 1) {
        if (item > t->left->data) {
            t->left = rotate_left(t->left);
        }
        t = rotate_right(t);
    } else if (r_height - l_height > 1) {
        if (item > t->right->data) {
            t->right = rotate_right(t->right);
        }
        t = rotate_left(t);
    }

    return t;
}

Tree tree_remove(Tree t, Item item) {
    // find the node with item
    if (t == NULL) {
        return NULL;
    } else if (item < t->data) {
        t->left = tree_remove(t->left, item);
    } else if (item > t->data) {
        t->right = tree_remove(t->right, item);
    } else {
        // once we find it, delete it
        t = delete_node(t);
    }
    return t;
}

bool tree_search(Tree t, Item item) {
    if (t == NULL) {
        return false;
    } else if (item < t->data) {
        return tree_search(t->left, item);
    } else if (item > t->data) {
        return tree_search(t->right, item);
    }
    return true;
}

void tree_show(Tree t) {
    if (t == NULL) {
        printf("<no tree created>\n");
        return;
    }
    printf("\n");
    tree_show_formatted(t, 0);
}

void tree_list(Tree t) {
	//printf("\n");
    //printf("  ");
    tree_list_formatted(t);
    printf("\n");
}

void tree_info(Tree t) {
    if (t == NULL) {

    }
    printf("\n");
    printf("format: |-> [data] ([height]) ([balance])\n");
    tree_info_formatted(t, 0);
}

// ---- helper functions ---- //
void tree_show_formatted(Tree t, int depth) {
    if (t != NULL) {
        tree_show_formatted(t->right, depth + 1);

        for (int i = 0; i < depth; i++) {
            printf("\t");
        }
        printf("%d\n", t->data);

        tree_show_formatted(t->left, depth + 1);
    }
}

void tree_list_formatted(Tree t) {
    if (t != NULL) {
		tree_list_formatted(t->left);
		printf("%d,", t->data);
		tree_list_formatted(t->right);
	}
}

void tree_info_formatted(Tree t, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    if (t != NULL) {
        int balance = calculate_height(t->left) - calculate_height(t->right);
        printf("|-> %d (%d) (%d)\n", t->data, t->height, balance);

        tree_info_formatted(t->left, depth + 1);
        tree_info_formatted(t->right, depth + 1);
    } else {
        printf("|-> []\n");
    }
}

// deletes a node and returns a pointer to the node that should take its place
Tree delete_node(Tree t) {
    Tree res = NULL;
    if (t->left == NULL && t->right == NULL) {
        res = NULL;
        free(t);
    } else if (t->right == NULL) {
        res = t->left;
        free(t);
    } else if (t->left == NULL) {
        res = t->right;
        free(t);
    } else { // if node has left and right
        // find minimum value to the right and set the current node to it's value
        t->data = find_min_value(t->right);
        // delete the minimum value to the right
        t->right = tree_remove(t->right, t->data);
        // return the same node
        res = t;
    }
    return res;
}

// returns the minimum value of a tree
Item find_min_value(Tree t) {
    Tree curr = t;
    while (curr->left != NULL) {
        curr = curr->left;
    }

    return curr->data;
}

Tree rotate_right(Tree t) {
    if (t == NULL) {
        return t;
    }

    if (t->left == NULL) {
        return t;
    }

    snprintf(buffer, MAX_LEN, "    rotating %d right\n", t->data);
    log_output(buffer);

    Tree left_child = t->left;
    t->left = left_child->right;
    left_child->right = t;

    // calculate height of left child and t
    if (t->left != NULL) {
        t->left->height = calculate_height(t->left);
    }
    if (t->right != NULL) {
        t->right->height = calculate_height(t->right);
    }
    t->height = calculate_height(t);
    left_child->height = calculate_height(left_child);

    return left_child;
}

Tree rotate_left(Tree t) {
    if (t == NULL) {
        return t;
    }
    
    if (t->right == NULL) {
        return t;
    }

    snprintf(buffer, MAX_LEN, "    rotating %d left\n", t->data);
    log_output(buffer);

    Tree right_child = t->right;
    t->right = right_child->left;
    right_child->left = t;

    // calculate height of right child and t
    if (t->left != NULL) {
        t->left->height = calculate_height(t->left);
    }
    if (t->right != NULL) {
        t->right->height = calculate_height(t->right);
    }
    t->height = calculate_height(t);
    right_child->height = calculate_height(right_child);

    return right_child;
}

int calculate_height(Tree t) {
    if (t == NULL) {
        return 0;
    }

    if (t->left == NULL && t->right == NULL) {
        return 1;
    }

    int l_height = 0;
    int r_height = 0;

    if (t->left != NULL) {
        l_height = t->left->height;
    }
    
    if (t->right != NULL) {
        r_height = t->right->height;
    }

    return max(l_height, r_height) + 1;
}

int max(int num1, int num2) {
    if (num1 > num2) {
        return num1;
    }
    return num2;
}
