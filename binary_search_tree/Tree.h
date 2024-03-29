#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef int Item;

typedef struct Node {
    Item data;
    struct Node *left;
    struct Node *right;
} Node;
typedef Node *Tree;

// create the binary search tree with inital item
Tree tree_create(Item);

// delete the entire binary search tree
Tree tree_delete(Tree);

// insert an element into the tree
Tree tree_insert(Tree, Item);

// remove an item from the tree
Tree tree_remove(Tree, Item);

// check if an item belongs to the tree
bool tree_search(Tree, Item);

// prints out the binary search tree
void tree_show(Tree);

// lists all values in binary tree in ascending order
void tree_list(Tree);

#endif
