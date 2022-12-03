#include <stdio.h>

#define MAX 1000000
#define TRUE 1
#define FALSE 0

void bubble_sort(int *nums, int size);

int main(void) {
    int nums[MAX];

    int curr;
    int count = 0;

    while (scanf("%d", &curr) != EOF && count < MAX) {
        nums[count] = curr;
        count++;
    }

    bubble_sort(nums, count);

    for (int i = 0; i < count; i++) {
        printf("%d\n", nums[i]);
    }

    return 0;
}

void bubble_sort(int *nums, int size) {
    int sorted = FALSE;
    while (sorted == FALSE) {
        sorted = TRUE;
        for (int i = 0; i < size - 1; i++) {
            if (nums[i] > nums[i + 1]) {
                int tmp = nums[i];
                nums[i] = nums[i + 1];
                nums[i + 1] = tmp;
                sorted = FALSE;
            }
        }
    }
}
