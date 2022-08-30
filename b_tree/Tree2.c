#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tree.h"
#include "colour.h"

typedef struct Node {
    int len; // keep track of length of data array
    Item data[ORDER];
    Tree child[ORDER + 1];
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
Tree tree_insert_here(Tree, Item, Tree l_child, Tree r_child);
void update_parent(Tree);
void tree_show_d(Tree, int depth, bool colour);

Tree tree_create(Item item) {
    Tree new_node = (Tree) malloc(sizeof(Node));
    new_node->data[0] = item;
    for (int i = 0; i < ORDER + 1; i++) {
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

    if (res == NULL) {
        return NULL;
    }

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
    tree_list(t->child[0]);
    for (int i = 0; i < t->len; i++) {
        printf("%d,", t->data[i]);
        tree_list(t->child[i + 1]);
    }
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

// inserts an item into t (returns address of node that item was ultimately inserted into)
Tree tree_insert_here(Tree t, Item item, Tree l_child, Tree r_child) {
    // this stuff should never happen
    if (t == NULL) {
        colour_red_b(true);
        printf("INSERT_HERE RECEIVED NULL\n");
        colour_reset(true);
        return t;
    }
    if (t->len >= ORDER) {
        colour_red_b(true);
        printf("NODE HAS LEN > %d\n", ORDER - 1);
        colour_reset(true);
        return t;
    }

    // logging action
    printf("insert %d into %p { length: %d }\n", item, t, t->len);

    // check if item already in node and return
    for (int i = 0; i < t->len; i++) {
        if (t->data[i] == item) {
            printf("    %d already in %p!\n", item, t);
            return t;
        }
    }

    // find place and insert
    int i = 0;
    while (t->data[i] < item && i < t->len) {
        i++;
    }

    printf("    inserting into index: %d\n", i);

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

    // update all children's parent value
    // for (int i = 0; i < t->len + 1; i++) {
    //     if (t->child[i] != NULL) {
    //         t->child[i]->parent = t;
    //     }
    // }
    update_parent(t);

    // if node has less items than ORDER, no split needed so return
    if (t->len < ORDER) {
        return t;
    }

    // logs
    printf("    splitting %p\n", t);

    // if ORDER elements (or greater), node split
    int middle_index = (ORDER - 1) / 2;

    Item promote_item = t->data[middle_index];

    Tree l_node = tree_create(t->data[0]);
    l_node->child[0] = t->child[0];
    for (int i = 1; i < middle_index; i++) { // transfer data to left node
        tree_insert_here(l_node, t->data[i], t->child[i], t->child[i + 1]);
    }
    l_node->child[middle_index] = t->child[middle_index];

    Tree r_node = tree_create(t->data[middle_index + 1]);
    r_node->child[0] = t->child[middle_index + 1];
    for (int i = middle_index + 2; i < ORDER; i++) {
        tree_insert_here(r_node, t->data[i], t->child[i], t->child[i + 1]);
    }

    update_parent(l_node);
    update_parent(r_node);

    Tree res = NULL;
    // if current node is root, create new node
    if (t->parent == NULL) {
        Tree parent = tree_create(promote_item);

        parent->child[0] = l_node;
        parent->child[1] = r_node;

        l_node->parent = parent;
        r_node->parent = parent;


        res = parent;

    } else { // split and insert into parent
        res = tree_insert_here(t->parent, promote_item, l_node, r_node);
    }

    free(t);

    return res;
}

void update_parent(Tree t) {
    for (int i = 0; i < t->len + 1; i++) {
        if (t->child[i] != NULL) {
            t->child[i]->parent = t;
        }
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
        printf("%p ", t); // node's current address
        colour_reset(colour);
        printf("(len: %d)", t->len); // node's length
        colour_black(colour);
        printf(" (parent: %p)", t->parent); // node's parent
        colour_reset(colour);
        printf("\n");

        for (int i = 0; i < ORDER; i++) {
            tree_show_d(t->child[i], depth + 1, colour);
        }
    }
}
