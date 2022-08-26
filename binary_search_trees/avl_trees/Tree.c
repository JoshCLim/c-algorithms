#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tree.h"

typedef struct Node {
    Item data;
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
Tree delete_node(Tree);
Item find_min_value(Tree);
Tree rotate_right(Tree);
Tree rotate_left(Tree);

// ---- interface functions ---- //
Tree tree_create(Item item) {
    Tree new_node = (Tree) malloc(sizeof(Node));
    new_node->data = item;
    new_node->left = NULL;
    new_node->right = NULL;

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

        t = new_node;
    } else if (item < t->data) { // else if curr value bigger than value, go left (and repeat/recurse)
        t->left = tree_insert(t->left, item);
    } else if (item > t->data) { // else if curr value smaller than value, go right (and repeat/recurse)
        t->right = tree_insert(t->right, item);
    } // else if curr value == value, already in tree so do nothing

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

    Tree left_child = t->left;
    t->left = left_child->right;
    left_child->right = t;

    return left_child;
}

Tree rotate_left(Tree t) {
    if (t == NULL) {
        return t;
    }
    
    if (t->right == NULL) {
        return t;
    }

    Tree right_child = t->right;
    t->right = right_child->left;
    right_child->left = t;

    return right_child;
}
