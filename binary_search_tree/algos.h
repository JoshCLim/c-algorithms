#ifndef ALGOS_H
#define ALGOS_H

#include <stdbool.h>
#include <stdlib.h>

#include "Tree.h"

// checks if a tree is a valid binary search tree
bool tree_validate(Tree);

// returns number of nodes in a Tree
int tree_num_nodes(Tree);

// returns height of the tree
int tree_height(Tree);
// checks if a tree is height balanced
bool tree_is_height_balanced(Tree);

// rotate a node left/right
Tree tree_rotate_right(Tree);
Tree tree_rotate_left(Tree);

// insert a value at the tree's root
Tree tree_insert_at_root(Tree, Item);

// returns minimum difference between two tree nodes
int tree_min_diff(Tree);

// returns kth smallest element in tree
Item tree_kth_smallest(Tree, int k);
// returns kth largest element in tree
Item tree_kth_largest(Tree, int k);

// traversals
void tree_print_inorder(Tree);
void tree_print_preorder(Tree);
void tree_print_postorder(Tree);
void tree_print_levelorder(Tree);

#endif
