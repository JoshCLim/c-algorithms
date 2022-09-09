#include <stdio.h>

#define MAX 10000

typedef int Item;

void merge_sort(Item a[], int lo, int hi);
void merge(Item a[], int lo, int mid, int hi);

int main(int argc, char *argv[]) {
    Item inputs[MAX];
    Item buffer;
    int length = 0;

    while (scanf("%d", &buffer) != EOF && length < MAX) {
        inputs[length++] = buffer;
    }

    printf("length: %d\n\n", length);

    merge_sort(inputs, 0, length - 1);

    for (int i = 0; i < length; i++) {
        printf("%d\n", inputs[i]);
    }

    return 0;
}

void merge_sort(Item a[], int lo, int hi) {
    if (lo >= hi) {
        return;
    }

    int mid = (hi + lo) / 2;

    merge_sort(a, lo, mid);
    merge_sort(a, mid + 1, hi);

    merge(a, lo, mid + 1, hi);
}

void merge(Item a[], int lo, int mid, int hi) {
    int i = lo;
    int j = mid;
    int z = 0;

    Item tmp[hi - lo + 1];

    while (i < mid && j <= hi) {
        if (a[i] < a[j]) {
            tmp[z++] = a[i++];
        } else {
            tmp[z++] = a[j++];
        }
    }
    while (i < mid) {
        tmp[z++] = a[i++];
    }
    while (j <= hi) {
        tmp[z++] = a[j++];
    }

    for (int q = 0; q < z; q++) {
        a[q + lo] = tmp[q];
    }
}