#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Tree.h"

#define HELP 'h'
#define CREATE 'c'
#define DELETE 'd'
#define INSERT 'i'
#define REMOVE 'r'
#define SEARCH 's'
#define SHOW 'p'

#define MAX_LEN 100

void help(void);
bool interpret_input(char input[MAX_LEN], char *tree, Item *item);

int main(void) {
    char input[MAX_LEN];
    Tree tree;
    Item item;

    char command = HELP;

    printf("Enter command: ");
    while (fgets(input, MAX_LEN, stdin) != NULL) {
        if (!interpret_input(input, &command, &item)) {
            printf("Enter command: ");
            continue;
        }

        if (command == HELP) {
            help();
        } else if (command == CREATE) {
            tree = tree_create(item);
        } else if (command == DELETE) {
            tree_delete(tree);
        } else if (command == INSERT) {
            tree = tree_insert(tree, item);
        } else if (command == REMOVE) {
            tree = tree_remove(tree, item);
        } else if (command == SEARCH) {
            fputs(tree_search(tree, item) ? "true" : "false", stdout);
            printf("\n");
        } else if (command == SHOW) {
            tree_show(tree);
        }

        printf("\n");
        printf("Enter command: ");
    }

    printf("\n");
    return 0;
}

void help(void) {
    printf("\n");
    printf("==========\n");
    printf("Usage:\n");
    printf("  help      h\n");
    printf("  create    c <item>\n");
    printf("  delete    d\n");
    printf("  insert    i <item>\n");
    printf("  remove    r <item>\n");
    printf("  search    s <item>\n");
    printf("  print     p\n");
    printf("==========\n");
    printf("\n");
}

bool interpret_input(char input[MAX_LEN], char *command, Item *item) {
    // remove newline character
    int i = 0;
    while (input[i] != '\n' && input[i] != '\0' && i < MAX_LEN) {
        i++;
    }
    input[i] = '\0';

    // read in input
    char *val0_str = NULL;
    char *val1_str = NULL;
    bool item_needed = false;

    // read command in
    val0_str = strtok(input, " ");
    if (val0_str != NULL) {
        if (val0_str[1] != ' ' && val0_str[1] != '\0') {
            val0_str = NULL;
            *command = -1;
        } else {
            *command = val0_str[0];
        }
    } else {
        *command = -1;
    }

    if (
        *command == CREATE ||
        *command == INSERT ||
        *command == REMOVE ||
        *command == SEARCH
    ) {
        item_needed = true;
        // read item in
        val1_str = strtok(NULL, " ");
        if (val1_str != NULL) {
            *item = atoi(val1_str);
        } else {
            *item = -1;
        }
    }

    if (val0_str == NULL || (val1_str == NULL && item_needed) || strtok(NULL, " ") != NULL) {
        printf("Invalid command. Enter 'h' for help.\n");
        return false;
    }

    return true;
}
