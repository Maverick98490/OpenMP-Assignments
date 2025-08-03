#include <stdio.h>
#include <omp.h>

int main() {
    int threads;

    printf("Enter no. of threads: ");
    scanf("%d", &threads);

    printf("\nSequential Hello:\n");
    for (int i = 0; i < threads; i++) {
        printf("Hello World from thread %d\n", i);
    }

    printf("\nParallel Hello:\n");
    omp_set_num_threads(threads);
    #pragma omp parallel
    {
        int p = omp_get_thread_num();
        printf("Hello World from thread %d \n", p);
    }

    return 0;
}
