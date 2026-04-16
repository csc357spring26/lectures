#include <stdlib.h>
#include <stdio.h>
#include "ops.h"

int reduce(int[], int, int (*)(int, int));
int *map(int[], int, int (*)(int));

int main(void) {
    int arr[] = {1, 2, 3, 4}, *tmp;

    printf("reduce(arr, 4, add): %d\n", reduce(arr, 4, add));
    printf("reduce(arr, 4, max): %d\n", reduce(arr, 4, max));

    tmp = map(arr, 4, inc);
    printf("map(arr, 4, inc):\n");
    printf(" |- %p: %d\n", (void *)&tmp[0], tmp[0]);
    printf(" |- %p: %d\n", (void *)&tmp[1], tmp[1]);
    printf(" |- %p: %d\n", (void *)&tmp[2], tmp[2]);
    printf(" +- %p: %d\n", (void *)&tmp[3], tmp[3]);

    /* NOTE: We the programmers uniquely know what problem our program is
     *       trying to solve, what our data represents, and therefore when
     *       we no longer need our memory. */
    free(tmp);

    return 0;
}

int reduce(int arr[], int n, int (*ptr)(int, int)) {
    int val = arr[0], i;

    /* NOTE: By taking as argument a pointer to a function containing the
     *       operation(s) to be performed inside this loop, this function can
     *       do different things simply by taking pointers to different
     *       functions as argument. */

    for (i = 1; i < n; i++) {
        val = ptr(val, arr[i]);
    }

    return val;
}

int *map(int arr[], int n, int (*ptr)(int)) {
    int i, *tmp;

    /* NOTE: By allocating the new array on the heap rather than on the stack,
     *       it will persist even after this function returns. Since array and
     *       pointer syntax is interchangeable, the compiler lets us pretend
     *       that a pointer to the heap is actually an array. */

    tmp = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        tmp[i] = ptr(arr[i]);
    }

    return tmp;
}
