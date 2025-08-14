#include <stdio.h>
#include <omp.h>

int main() {
    int i, j;
    int rows = 3, cols = 3;

    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int vector[3] = {1, 2, 3};
    int result[3] = {0};

    double start = omp_get_wtime();

    #pragma omp parallel for private(j) shared(matrix, vector, result)
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    double end = omp_get_wtime();

    printf("Result Vector:\n");
    for (i = 0; i < rows; i++) {
        printf("%d ", result[i]);
    }
    printf("\nTime taken: %f seconds\n", end - start);

    return 0;
}
