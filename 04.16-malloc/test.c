#include <stdlib.h>
#include <stdio.h>
#include "ops.h"

/* NOTE: A function pointer must be declared as pointing a function of a
 *       particular type signature, so that the compiler knows what should
 *       happen when it's dereferenced. Note the only scenario in which it makes
 *       sense to dereference a function pointer is to call the function. */
int reduce(int[], int, int (*)(int, int));
int *map(int [], int, int (*)(int));

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

    /* NOTE: We the programmers uniquely know what our data represents and
     *       thus when we no longer need it. If we allocate data dynamically,
     *       then it is our responsibility to deallocate that data once it is
     *       no longer needed, so as to avoid any memory leaks. */
    free(tmp);

    return 0;
}

/* NOTE: By having this function take as argument a pointer to another function
 *       that combines the individual elements of the array, we can use the
 *       same logic to perform different operations by passing pointers to
 *       different functions. */
int reduce(int arr[], int n, int (*ptr)(int, int)) {
    int val = arr[0], i;

    for (i = 1; i < n; i++) {
        val = ptr(val, arr[i]);
    }

    return val;
}

/* NOTE: Since a reference to an array is the address of its first element, it
 *       is never safe to return an array -- we would just be returning the
 *       address of a local that is about to be deallocated. Instead, we can
 *       allocate space for the array on the heap, which will persist. */
int *map(int arr[], int n, int (*ptr)(int)) {
    int i, *tmp;

    tmp = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        tmp[i] = ptr(arr[i]);
    }

    return tmp;
}
