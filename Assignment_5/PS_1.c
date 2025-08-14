#include <stdio.h>
#include <omp.h>

int main() {
    int m = 3, n = 3, p = 3; 
    int A[3][3] = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    int B[3][3] = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    int C[3][3];
    double start, end;

    for(int i=0; i<m; i++)
        for(int j=0; j<p; j++)
            C[i][j] = 0;

    start = omp_get_wtime();

    #pragma omp parallel for collapse(2) shared(A,B,C)
    for(int i=0; i<m; i++) {
        for(int j=0; j<p; j++) {
            int sum = 0;
            for(int k=0; k<n; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    end = omp_get_wtime();

    printf("Result Matrix C:\n");
    for(int i=0; i<m; i++) {
        for(int j=0; j<p; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    printf("Time taken: %lf seconds\n", end - start);

    return 0;
}
