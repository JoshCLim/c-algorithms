#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define MAX 100000

typedef int Item;

void quicksort(Item a[], int lo, int hi);
void swapItems(Item a[], int index1, int index2);

int main(void) {
    Item inputs[MAX];
    int length = 0;
    Item buffer = 0;

    while ((scanf(" %d", &buffer) != EOF) && length < MAX) {
        inputs[length++] = buffer;
    }

    quicksort(inputs, 0, length - 1);

    for (int i = 0; i < length; i++) {
        printf("%d\n", inputs[i]);
    }

    return 0;
}

void quicksort(Item a[], int lo, int hi) {
    if (lo >= hi) {
        return;
    }

    Item pivot_value = a[lo];

    int i = lo + 1;
    int j = hi;
    
    while (true) {
        while (i < j && a[i] <= pivot_value) i++;
        while (i < j && a[j] > pivot_value) j--;
        if (i == j) break;
        swapItems(a, i, j);
    }

    assert(i == j);

    int pivot_new_pos = (a[i] < pivot_value) ? i : i - 1;

    printf("about to recurse\n");
    quicksort(a, lo, pivot_new_pos - 1);
    quicksort(a, pivot_new_pos + 1, hi);
}

void swapItems(Item a[], int index1, int index2) {
    Item tmp = a[index1];
    a[index1] = a[index2];
    a[index2] = tmp;
}
