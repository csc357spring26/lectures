#include <stdio.h>
#include "swap.h"

/* NOTE: An array of pointers decays into a double pointer, and since pointer
 *       and array syntax is interchangeable, we can then access that double
 *       pointer as though it were an array. */
void f(int **mat) {
    mat[0][1] = 5;
}

/* NOTE: Since multidimensional arrays are stored in "row-major order", the
 *       compiler must know the length of each "inner" array in order to index
 *       it. However, this function only works on n x 2 arrays... */
void g(int mat[][2]) {
    mat[0][1] = 6;
}

/* NOTE: ...if we instead pass an n x m array as an ordinary pointer, since we
 *       the programmers know that it's actually the address of a 2D array, we
 *       can do the indexing math for the compiler. */
void h(int *mat, int width) {
    *(mat + (0 * width) + 1) = 7;
}

int main(void) {
    int arr[] = {1, 2, 3, 4};
    int row0[] = {1, 2}, row1[] = {3, 4};
    int *mat1[2];
    int mat2[][2] = {{1, 2}, {3, 4}};

    mat1[0] = row0;
    mat1[1] = row1;

    reverse(arr, 4);

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" |- %p: %d\n", (void *)&arr[1], arr[1]);
    printf(" |- %p: %d\n", (void *)&arr[2], arr[2]);
    printf(" +- %p: %d\n", (void *)&arr[3], arr[3]);

    f(mat1);

    printf("mat1: %p\n", (void *)mat1);
    printf(" |- %p: %p\n", (void *)&mat1[0], (void *)mat1[0]);
    printf(" |   |- %p: %d\n", (void *)&mat1[0][0], mat1[0][0]);
    printf(" |   +- %p: %d\n", (void *)&mat1[0][1], mat1[0][1]);
    printf(" +- %p: %p\n", (void *)&mat1[1], (void *)mat1[1]);
    printf("     |- %p: %d\n", (void *)&mat1[1][0], mat1[1][0]);
    printf("     +- %p: %d\n", (void *)&mat1[1][1], mat1[1][1]);

    g(mat2);
    h((int *)mat2, 2);

    printf("mat2: %p\n", (void *)mat2);
    printf(" |- %p: %p\n", (void *)&mat2[0], (void *)mat2[0]);
    printf(" |   |- %p: %d\n", (void *)&mat2[0][0], mat2[0][0]);
    printf(" |   +- %p: %d\n", (void *)&mat2[0][1], mat2[0][1]);
    printf(" +- %p: %p\n", (void *)&mat2[1], (void *)mat2[1]);
    printf("     |- %p: %d\n", (void *)&mat2[1][0], mat2[1][0]);
    printf("     +- %p: %d\n", (void *)&mat2[1][1], mat2[1][1]);

    return 0;
}
