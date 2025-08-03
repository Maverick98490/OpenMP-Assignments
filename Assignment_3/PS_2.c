#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void fill_matrix(int **mat, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % 10;
}

double add_matrices(int **A, int **B, int **C, int n) {
    double start = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];

    double end = omp_get_wtime();
    return end - start;
}

int** alloc_matrix(int n) {
    int **mat = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        mat[i] = malloc(n * sizeof(int));
    return mat;
}

void free_matrix(int **mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {1, 2, 4, 8};

    for (int s = 0; s < 5; s++) {
        int n = sizes[s];
        int **A = alloc_matrix(n);
        int **B = alloc_matrix(n);
        int **C = alloc_matrix(n);

        fill_matrix(A, n);
        fill_matrix(B, n);

        printf("\nMatrix Size: %d x %d\n", n, n);
        double baseline = 0;

        for (int t = 0; t < 4; t++) {
            omp_set_num_threads(threads[t]);
            double time = add_matrices(A, B, C, n);

            if (threads[t] == 1)
                baseline = time;

            double speedup = baseline / time;

            printf("Threads: %d, Time: %.6f s, Speedup: %.2f\n", threads[t], time, speedup);
        }

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }

    return 0;
}
