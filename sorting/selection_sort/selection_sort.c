#include <stdio.h>

#define MAX 1000

typedef int Item;

void selection_sort(Item a[], int lo, int hi);

int main(int argc, char* argv[]) {
    Item inputs[MAX];
    int length = 0;
    Item buffer = 0;

    while(scanf("%d", &buffer) != EOF && length < MAX) {
        inputs[length++] = buffer;
    }

    printf("length: %d\n\n", length);

    selection_sort(inputs, 0, length - 1);

    for (int i = 0; i < length; i++) {
        printf("%d\n", inputs[i]);
    }

    return 0;
}

void selection_sort(Item a[], int lo, int hi) {
    for (int i = lo; i <= hi; i++) {
        // find min
        int min = i;
        for (int j = i + 1; j <= hi; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        // swap a[i-1] and a[min]
        Item tmp = a[min];
        a[min] = a[i];
        a[i] = tmp;
    }
}
