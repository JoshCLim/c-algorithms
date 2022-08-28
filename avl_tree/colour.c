#include <stdio.h>
#include <stdbool.h>

void colour_reset(bool mode) {
    if (mode == false) {
        return;
    }
    printf("\033[0m");
}

void colour_red_b(bool mode) {
    if (mode == false) {
        return;
    }
    printf("\033[1;31m");
}

void colour_black(bool mode) {
    if (mode == false) {
        return;
    }
    printf("\033[0;30m");
}

void colour_green(bool mode) {
    if (mode == false) {
        return;
    }
    printf("\033[0;32m");
}
