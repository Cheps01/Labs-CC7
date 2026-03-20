#include <stdio.h>
#include "threads.h"

#define THREADS 10
#define N 2

int main() {
    pthread_t thread[THREADS];
    int ids[THREADS];
    pthread_mutex_init(&lock, NULL);
    sem_init(&entry, 1, N);

    for (int i=0; i<THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&thread[i], NULL, run_thread, &ids[i]);
    }
    for (int j=0; j<THREADS; j++) {
        pthread_join(thread[j], NULL);
    }
    sem_destroy(&entry);

    printf("Total parked cars: %d\n", parked_cars);
    printf("Average waiting time: %.2f\n", (double)(total_wait / parked_cars));

    return 0;
}