#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 200

void initialize_vector(float *vec, int size) {
    for (int i = 0; i < size; i++) {
        vec[i] = i;
    }
}

double vector_add_static(float *vec, float scalar, int chunk_size, int threads) {
    double start = omp_get_wtime();

    omp_set_num_threads(threads);
    #pragma omp parallel for schedule(static, chunk_size)
    for (int i = 0; i < SIZE; i++) {
        vec[i] += scalar;
    }

    return omp_get_wtime() - start;
}

double vector_add_dynamic(float *vec, float scalar, int chunk_size, int threads) {
    double start = omp_get_wtime();

    omp_set_num_threads(threads);
    #pragma omp parallel for schedule(dynamic, chunk_size)
    for (int i = 0; i < SIZE; i++) {
        vec[i] += scalar;
    }

    return omp_get_wtime() - start;
}

void nowait_example(float *vec1, float *vec2) {
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for nowait
        for (int i = 0; i < SIZE / 2; i++) {
            vec1[i] += 5;
        }

        #pragma omp for
        for (int i = SIZE / 2; i < SIZE; i++) {
            vec2[i] += 10;
        }
    }
}

int main() {
    float vec1[SIZE], vec2[SIZE];
    float scalar = 2.0;

    initialize_vector(vec1, SIZE);
    initialize_vector(vec2, SIZE);

    int chunks[] = {1, 5, 10, 25, 50};
    int thread_count = 4;

    printf("Static Scheduling:\n");
    for (int i = 0; i < 5; i++) {
        initialize_vector(vec1, SIZE);
        double time = vector_add_static(vec1, scalar, chunks[i], thread_count);
        printf("Chunk size: %d | Time: %f sec\n", chunks[i], time);
    }

    printf("\nDynamic Scheduling:\n");
    for (int i = 0; i < 5; i++) {
        initialize_vector(vec2, SIZE);
        double time = vector_add_dynamic(vec2, scalar, chunks[i], thread_count);
        printf("Chunk size: %d  Time: %f sec\n", chunks[i], time);
    }

    return 0;
}
