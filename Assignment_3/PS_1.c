#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n, i;
    double seq_time, par_time;

    printf("Enter size of vectors: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));
    int *B = malloc(n * sizeof(int));

    printf("Enter elements of vector A:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    printf("Enter elements of vector B:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }

    int dot_product = 0;

    // Sequential version (1 thread)
    omp_set_num_threads(1);
    double start_time = omp_get_wtime();

    for (i = 0; i < n; i++) {
        dot_product += A[i] * B[i];
    }

    double end_time = omp_get_wtime();
    seq_time = end_time - start_time;

    printf("Dot product (1 thread) = %d\n", dot_product);
    printf("Time with 1 thread: %f seconds\n", seq_time);

    // Parallel version (4 threads)
    dot_product = 0;
    omp_set_num_threads(4);
    start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:dot_product)
    for (i = 0; i < n; i++) {
        dot_product += A[i] * B[i];
    }

    end_time = omp_get_wtime();
    par_time = end_time - start_time;

    printf("Dot product (4 threads) = %d\n", dot_product);
    printf("Time with 4 threads: %f seconds\n", par_time);
    printf("Speedup: %.2f\n", seq_time / par_time);

    free(A);
    free(B);
    return 0;
}
