#include <stdio.h>
#include <omp.h>

#define SIZE 5
#define PRODUCE_COUNT 10

int buffer[SIZE];
int count = 0;

omp_lock_t lock;

void producer() {
    for (int i = 1; i <= PRODUCE_COUNT; i++) {
        int produced = i * 10;
        omp_set_lock(&lock);
        if (count < SIZE) {
            buffer[count] = produced;
            count++;
            printf("Producer produced: %d | Buffer count: %d\n", produced, count);
        }
        omp_unset_lock(&lock);
    }
}

void consumer() {
    for (int i = 1; i <= PRODUCE_COUNT; i++) {
        omp_set_lock(&lock);
        if (count > 0) {
            int consumed = buffer[count - 1];
            count--;
            printf("Consumer consumed: %d | Buffer count: %d\n", consumed, count);
        }
        omp_unset_lock(&lock);
    }
}

int main() {
    omp_init_lock(&lock);
    double start = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        producer();

        #pragma omp section
        consumer();
    }

    double end = omp_get_wtime();
    printf("\nTime taken: %f seconds\n", end - start);

    omp_destroy_lock(&lock);
    return 0;
}
