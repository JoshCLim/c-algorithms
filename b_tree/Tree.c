#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tree.h"
#include "colour.h"

typedef struct Node {
    int len; // keep track of length of data array
    Item data[ORDER - 1];
    Tree child[ORDER];
    Tree parent;
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

Tree tree_insert_search(Tree, Item);
Tree tree_insert_here(Tree t, Item item, Tree l_child, Tree r_child);
void tree_show_d(Tree, int depth, bool colour);

Tree tree_create(Item item) {
    Tree new_node = (Tree) malloc(sizeof(Node));
    new_node->data[0] = item;
    for (int i = 0; i < ORDER; i++) {
        new_node->child[i] = NULL;
    }
    new_node->parent = NULL;
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
    Tree insert_node = tree_insert_search(t, item);

    // return tree_insert_here(insert_node, item, NULL, NULL);
    Tree res = tree_insert_here(insert_node, item, NULL, NULL);

    while (res->parent != NULL) {
        res = res->parent;
    }

    printf("\n");
    tree_show(res, true);
    return res;
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
    if (t == NULL) {
        return;
    }


    return;
}

// ---- helper functions ---- //

// returns address of node to insert into
Tree tree_insert_search(Tree t, Item item) {
    if (t == NULL) {
        return NULL;
    }
    // if (t->len < ORDER - 1) {
    //     return t;
    // }

    int i = 0;
    while (t->data[i] < item && i < ORDER - 1 && i < t->len) {
        printf("%d < %d\n", t->data[i], item);
        i++;
    }
    printf("%d\n", i);

    if (t->data[i] == item) {
        return t;
    }

    if (tree_insert_search(t->child[i], item) == NULL) {
        return t;
    }

    return tree_insert_search(t->child[i], item);
}

Tree tree_insert_here(Tree t, Item item, Tree l_child, Tree r_child) {
    if (t == NULL) { // should never run
        colour_red_b(true);
        printf("THIS SHOULD NEVER RUN?\n");
        colour_reset(true);
        Tree new_node = tree_create(item);

        new_node->child[0] = l_child;
        new_node->child[1] = r_child;

        return new_node;
    }

    printf("insert %d into %p { length: %d }\n", item, t, t->len);

    for (int i = 0; i < t->len; i++) {
        if (t->data[i] == item) {
            printf("    %d already in %p!\n", item, t);
            return t;
        }
    }

    if (t->len < ORDER - 1) {
        int i = 0;
        while (t->data[i] < item && i < t->len) {
            i++;
        }

        printf("    inserting into index: %d\n", i);

        if (t->data[i] == item) {
            // if item already in node, do nothing
            return t;
        }

        t->len++; // add one to node length

        t->child[i] = l_child;
        while (i < t->len) { // insert item and shift everything over
            Item tmp_item = t->data[i];
            Tree tmp_child = t->child[i + 1];


            t->data[i] = item;
            t->child[i + 1] = r_child;

            item = tmp_item;
            r_child = tmp_child;
            i++;
        }

        return t;

    } else {
        int middle_index = (ORDER - 1) / 2;

        Item promote_item = t->data[middle_index];
        
        // node split
        Tree l_node = tree_create(t->data[0]);
        l_node->child[0] = t->child[0];
        for (int i = 1; i < middle_index; i++) { // transfer data to left node
            tree_insert_here(l_node, t->data[i], t->child[i], t->child[i + 1]);
        }

        Tree r_node = tree_create(t->data[middle_index + 1]);
        r_node->child[0] = t->child[middle_index + 1];
        for (int i = middle_index + 2; i < ORDER - 1; i++) {
            tree_insert_here(r_node, t->data[i], t->child[i], t->child[i + 1]);
        }

        printf("    promoting %d\n", promote_item);

        Tree parent = t->parent;
        Tree res = NULL;
        if (parent == NULL) {
            parent = tree_create(promote_item);

            parent->child[0] = l_node;
            parent->child[1] = r_node;

            res = parent;
        } else {
            res = tree_insert_here(parent, promote_item, l_node, r_node);
        }
        l_node->parent = parent;
        r_node->parent = parent;

        if (item < promote_item) {
            tree_insert_here(l_node, item, l_child, r_child);
        } else if (item > promote_item) {
            tree_insert_here(r_node, item, l_child, r_child);
        }

        printf("    freeing %p\n", t);
        free(t);

        printf("insert function returns %p\n", res);

        return res;
        // tree_insert_here(parent, promote_item, l_node, r_node);
    }
}

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
        printf("] ");
        colour_black(colour);
        printf("%p ", t);
        colour_reset(colour);
        printf("(len: %d)", t->len);
        colour_black(colour);
        printf(" (parent: %p)", t->parent);
        colour_reset(colour);
        printf("\n");

        for (int i = 0; i < ORDER; i++) {
            tree_show_d(t->child[i], depth + 1, colour);
        }
    }
}
