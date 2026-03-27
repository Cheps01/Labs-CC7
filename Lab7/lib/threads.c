#include "threads.h"

// Thread initialization utility.
void init_threads(int n, Function fn) {
    pthread_t threads[n];
    int ids[n];
    for (int i=0; i<n; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, fn, &ids[i]);
    }
    for (int j=0; j<n; j++) {
        pthread_join(threads[j], NULL);
    }
}
// Thread lock for critical section
void lock(pthread_mutex_t *mutex) {
    pthread_mutex_lock(mutex);
}
// Thread unlock for exiting critical section
void unlock(pthread_mutex_t *mutex) {
    pthread_mutex_unlock(mutex);
}
void wait(pthread_cond_t *cond, pthread_mutex_t *mutex) {
    pthread_cond_wait(cond, mutex);
}
void signal(pthread_cond_t *cond) {
    pthread_cond_signal(cond);
}
void broadcast(pthread_cond_t *cond) {
    pthread_cond_broadcast(cond);
}