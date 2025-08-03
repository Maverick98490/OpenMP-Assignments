#include <stdio.h>
#include <omp.h>

int main() {
    long steps;
    double step_size;
    double pi = 0.0;
    double x;
    int i;

    printf("Enter number of steps: ");
    scanf("%ld", &steps);

    step_size = 1.0 / (double)steps;

    double start_time = omp_get_wtime();

    #pragma omp parallel for private(x) reduction(+:pi)
    for (i = 0; i < steps; i++) {
        x = (i + 0.5) * step_size;
        pi += 4.0 / (1.0 + x * x);
    }

    pi = pi * step_size;

    double end_time = omp_get_wtime();

    printf("Calculated value of Pi = %.15f\n", pi);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
