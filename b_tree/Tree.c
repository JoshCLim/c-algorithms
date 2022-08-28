#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tree.h"
#include "colour.h"

typedef struct Node {
    int len; // keep track of length of data array
    Item data[ORDER - 1];
    struct Node *child[ORDER];
} Node;

// ---- function prototypes ---- //
Tree tree_create(Item);
Tree tree_delete(Tree);
Tree tree_insert(Tree, Item);
Tree tree_remove(Tree, Item);
bool tree_search(Tree, Item);
void tree_show(Tree, bool);
void tree_list(Tree);
// void tree_info(Tree, bool);

void tree_show_d(Tree, int depth, bool colour);

Tree tree_create(Item item) {
    Tree new_node = (Tree) malloc(sizeof(Node));
    new_node->data[0] = item;
    for (int i = 0; i < ORDER; i++) {
        new_node->child[i] = NULL;
    }
    new_node->len = 1;

    return new_node;
}

Tree tree_delete(Tree t) {
    if (t != NULL) {
        for (int i = 0; i < ORDER; i++) {
            tree_delete(t->child[i]);
        }
        free(t);
    }
    return NULL;
}

Tree tree_insert(Tree t, Item item) {
    return NULL;
}
Tree tree_remove(Tree t, Item item) {
    return NULL;
}
bool tree_search(Tree t, Item item) {
    return false;
}


void tree_show(Tree t, bool colour) {
    if (t == NULL) {
        printf("no tree created\n");
        return;
    }
    tree_show_d(t, 0, colour);
}

void tree_list(Tree t) {
    return;
}

// ---- helper functions ---- //
void tree_show_d(Tree t, int depth, bool colour) {
    if (t == NULL) {
        for (int i = 0; i < depth; i++) {
            printf("    ");
        }
        colour_black(colour);
        printf("|-> []");
        colour_reset(colour);
        printf("\n");
    } else {
        for (int i = 0; i < depth; i++) {
            printf("    ");
        }
        colour_black(colour);
        printf("|-> ");
        colour_reset(colour);
        printf("[");
        for (int i = 0; i < t->len; i++) {
            printf("%d", t->data[i]);
            if (i < ORDER - 2) {
                printf(",");
            }
        }
        for (int i = t->len; i < ORDER - 1; i++) {
            printf(" ");
            if (i < ORDER - 2) { 
                printf(",");
            }
        }
        printf("]\n");

        for (int i = 0; i < ORDER; i++) {
            tree_show_d(t->child[i], depth + 1, colour);
        }
    }
}
