#include <stdio.h>
#include <omp.h>

int main() {
    int rows = 3, cols = 3;
    int i, j;
    int scalar = 5;

    int A[3][3] = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    int result[3][3];

    double start = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[i][j] = A[i][j] * scalar;
        }
    }

    double end = omp_get_wtime();

    printf("Result Matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    printf("Time taken: %f seconds\n", end - start);

    return 0;
}
