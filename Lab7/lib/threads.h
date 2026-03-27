#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

typedef void *(*Function)(void*);

void init_threads(int n, Function fn);
void lock(pthread_mutex_t *lock);
void unlock(pthread_mutex_t *lock);
void wait(pthread_cond_t *cond, pthread_mutex_t *lock);
void signal(pthread_cond_t *cond);
void broadcast(pthread_cond_t *cond);

#endif // THREADS_H