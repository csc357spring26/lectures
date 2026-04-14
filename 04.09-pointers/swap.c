#include <stdio.h>

/* NOTE: In C, arguments are always pass-by-value, but the value of a pointer
 *       is a reference. By passing pointers, we can emulate pass-by-reference
 *       behavior whenever we want. */
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;

    printf("x (%p): %p\n", (void *)&x, (void *)x);
    printf("y (%p): %p\n", (void *)&y, (void *)y);
}
