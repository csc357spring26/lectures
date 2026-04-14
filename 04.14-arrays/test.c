#include <stdio.h>
#include "swap.h"

/* NOTE: Pointers are variables in their own right, and they can be collected
 *       into arrays just like ordinary variables. An array of pointers thus
 *       decays into a double pointer when passed as argument. */
void f(int **mat) {
    mat[1][0] = 5;
}

/* NOTE: Multidimensional arrays are stored in "row-major order": a 2D array is
 *       an array of rows, and the compiler must know the length of each row in
 *       order to index the array. This only works on n x 2 arrays...*/
void g(int mat[][2]) {
    mat[1][0] = 6;
}

/* NOTE: ...since we the programmers know that this is not actually an ordinary
 *       pointer, but instead the beginning of a 2D array, we can do the
 *       indexing math for the compiler in order to accept any n x m array. */
void h(int *mat, int width) {
    *(mat + (1 * width) + 0) = 7;
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
