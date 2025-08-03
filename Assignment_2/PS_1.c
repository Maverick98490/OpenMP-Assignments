#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n, scalar;
    double *vec;
    int i;

    printf("Enter size of vector: ");
    scanf("%d", &n);

    printf("Enter scalar value to add: ");
    scanf("%d", &scalar);

    vec = (double *)malloc(n * sizeof(double));

    for (i = 0; i < n; i++) {
        vec[i] = i * 1.0;
    }

    double start_time = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        vec[i] = vec[i] + scalar;
    }

    double end_time = omp_get_wtime();

    printf("Time taken: %f seconds\n", end_time - start_time);

    for (i = 0; i < 5 && i < n; i++) {
        printf("vec[%d] = %f\n", i, vec[i]);
    }

    free(vec);

    return 0;
}
