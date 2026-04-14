#include <stdio.h>
#include "swap.h"

int main(void) {
    int z = 1, w = 2;

    /* NOTE: Essentially, by telling a function *where* a value can be found
     *       rather than *what* a value is, we can give any function access to
     *       any other function's local variables! */
    swap(&z, &w);

    printf("z (%p): %d\n", (void *)&z, z);
    printf("w (%p): %d\n", (void *)&w, w);

    /* NOTE: A NULL pointer is guaranteed to be an invalid address, and so
     *       dereferencing a NULL pointer will result in a segfault. A segfault
     *       is never ideal, but consistent failure is better than randomness.
     * swap(NULL, NULL); */

    return 0;
}
