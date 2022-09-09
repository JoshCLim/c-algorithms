#include <stdio.h>

#define MAX 1000

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
    for (int i = lo + 1; i <= hi; i++) {
        int value_to_insert = a[i];

        for (int j = i; j > lo; j--) {
            if (value_to_insert > a[j - 1]) {
                a[j] = value_to_insert;
                break;
            }
            a[j] = a[j - 1];
        }
    }
}