#include "threads.h"
#include "parking.h"
#include "utils.h"

pthread_mutex_t lock;            // lock for shared resources 
sem_t entry;                     // parking access semaphore

int parked_cars;
int total_wait;

void enter(int id) {
    pthread_mutex_lock(&lock);
    set_spot(id);
    pthread_mutex_unlock(&lock);
}
void leave(int id) {
    pthread_mutex_lock(&lock);
    clear_spot(id);
    pthread_mutex_unlock(&lock);
}
void *run_thread(void *arg) {
    int id = *(int *)arg;
    thread_log(id, "Arrived at parking lot.\n");
    time_t start = start_time();

    sem_wait(&entry);
    enter(id);
    thread_log(id, "Parked succesfully. ");

    double wait = finish_time(start);
    printf("Waited %.2f seconds \n", wait);
    parked_cars++;
    total_wait += wait;

    sleep(randint(1, 5));
    leave(id);
    sem_post(&entry);
    
    thread_log(id, "Leaving parking lot.\n");
    return NULL;
}