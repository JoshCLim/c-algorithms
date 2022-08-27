#include <stdio.h>

void colour_reset() {
    printf("\033[0m");
}

void colour_red_b() {
    printf("\033[1;31m");
}

void colour_black() {
    printf("\033[0;30m");
}

void colour_green() {
    printf("\033[0;32m");
}