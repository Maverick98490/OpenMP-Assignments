#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n, i;
    printf("Enter size of vectors: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));
    int *B = malloc(n * sizeof(int));

    printf("Enter elements of vector A:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    printf("Enter elements of vector B:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }

    int dot_product = 0;

    for(i = 0; i < n; i++) {
        dot_product += A[i] * B[i];
    }

    printf("Scalar (dot) product = %d\n", dot_product);

    free(A);
    free(B);

    return 0;
}
