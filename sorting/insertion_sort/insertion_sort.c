#include <stdio.h>

#define MAX 10000

typedef int Item;

void insertion_sort(Item a[], int lo, int hi);

int main(int argc, char* argv[]) {
    Item inputs[MAX];
    int length = 0;
    Item buffer = 0;

    while(scanf("%d", &buffer) != EOF && length < MAX) {
        inputs[length] = buffer;
        length++;
    }

    insertion_sort(inputs, 0, length - 1);

    for (int i = 0; i < length; i++) {
        printf("%d\n", inputs[i]);
    }

    return 0;
}

void insertion_sort(Item a[], int lo, int hi) {
    int i, j, value_to_insert;

    for (i = lo + 1; i <= hi; i++) {
        value_to_insert = a[i];

        for (j = i; j > lo; j--) {
            if (value_to_insert > a[j - 1]) {
                break;
            }
            a[j] = a[j - 1]; // shift value right
        }
        a[j] = value_to_insert;
    }
}
