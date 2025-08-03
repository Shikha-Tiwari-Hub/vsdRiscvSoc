#include "unique.h"

int main(void) {
    uniq_print_header("max_array");

    int arr[] = {3, 7, 11, 19, 5, 9};
    int max = arr[0];

    for (int i = 1; i < 6; ++i) {
        if (arr[i] > max)
            max = arr[i];
    }

    printf("Maximum = %d\n", max);
    return 0;
}

