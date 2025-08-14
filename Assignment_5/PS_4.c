#include <stdio.h>
#include <omp.h>

int main() {
    int n = 8;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int prefix[n];
    double start_time, end_time;

    start_time = omp_get_wtime();

    prefix[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + arr[i];
    }

    end_time = omp_get_wtime();

    printf("Prefix Sum Array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", prefix[i]);
    }
    printf("\nTime taken: %f seconds\n", end_time - start_time);

    return 0;
}
