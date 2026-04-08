#include <stdio.h>
#include "swap.h"

int main(void) {
    int z = 1, w = 2;

    swap(z, w);

    printf("z: %d\n", z);
    printf("w: %d\n", w);

    return 0;
}
