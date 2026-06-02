#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 512
#define THREADS 2

int main(int argc, char *argv[]) {
    int arr[SIZE], i, n, x, count;

    for (i = 0; i < SIZE; i++) {
        arr[i] = rand() % 10;
    }

    x = strtol(argv[1], NULL, 10);
    n = SIZE;

    for (i = 0; i < n; i++) {
        if (arr[i] == x) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
