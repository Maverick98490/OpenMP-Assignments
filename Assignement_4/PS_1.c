#include <stdio.h>
#include <omp.h>

long fibonacci_calc(int n) {
    if (n < 2) return n;
    long a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int main() {
    int N = 20;
    long fib[20];
    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        fib[i] = fibonacci_calc(i);
    }

    double end = omp_get_wtime();

    printf("Fibonacci Series up to %d terms:\n", N);
    for (int i = 0; i < N; i++) {
        printf("%ld ", fib[i]);
    }
    printf("\nTime taken: %f seconds\n", end - start);

    return 0;
}
