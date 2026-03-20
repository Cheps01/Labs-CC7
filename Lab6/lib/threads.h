#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

extern pthread_mutex_t lock;   
extern sem_t entry;

extern int parked_cars;
extern int total_wait;

void *run_thread(void *arg);

#endif // THREADS_H