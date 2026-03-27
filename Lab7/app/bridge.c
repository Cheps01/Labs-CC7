#include "bridge.h"

#define MAX 4                                          // maximum bridge capacity

pthread_cond_t  right = PTHREAD_COND_INITIALIZER;      // ok to move right condition variable
pthread_cond_t  left  = PTHREAD_COND_INITIALIZER;      // ok to move left condition variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;     // lock for shared resources

double total_wait = 0;                                 // total amount of time waiting (seconds)
int total_students = 0;                                // total students that cross the bridge
int on_bridge = 0;                                     // current amount of students crossing the bridge
int current_dir;                                       // current direction in which students are going
int waiting_right = 0;                                 // students waiting to move right
int waiting_left = 0;                                  // students waiting to move left

// Access bridge functionality.
// The student goes in if the current direction is the same with it's own and there's room for it.
void access_bridge(int dir) {
    lock(&mutex);
    if (!waiting_left && !waiting_right && !on_bridge) 
        current_dir = dir;
    while (current_dir != dir || on_bridge == MAX) {
        if (dir) {
            waiting_left++;
            wait(&left, &mutex);
            waiting_left--;
        } else {
            waiting_right++;
            wait(&right, &mutex);
            waiting_right--;
        }
    }
    on_bridge++;
    unlock(&mutex);
}
// Exit bridge functionality. 
// As it exits it checks if it's the last and changes the direction to balance the opposing side.
void exit_bridge() {
    lock(&mutex);
    on_bridge--;
    if (on_bridge == 0) {
        if (waiting_left < waiting_right) {
            current_dir = 0;
            broadcast(&right);
        } else if (waiting_left > waiting_right) {
            current_dir = 1;
            broadcast(&left);
        }
    } else if (current_dir == 0 && waiting_right > 0 && on_bridge < MAX) {
        signal(&right);
    } else if (current_dir == 1 && waiting_left > 0 && on_bridge < MAX) {
        signal(&left);
    }
    unlock(&mutex);
}   
// Student thread life-cycle.
// Logging includes the moment it arrives, crosses and exits. 
void *student_cross_bridge(void *arg) {
    int id = *(int *)arg;
    int dir = randint(0,1); // 1 -> left, 0 -> right
    if (dir)
        printf("Inge %d arrives wanting to go left.\n", id); 
    else
        printf("Inge %d arrives wanting to go right.\n", id);
    time_t start = start_timer();
    // Wait after arriving
    sleep(randint(0,5));
    // Access bridge
    access_bridge(dir);
    double elapsed = end_timer(start);
    total_wait += elapsed;
    if (dir) 
        printf("Inge %d crosses to the left. (on bridge: %d)\n", id, on_bridge);
    else 
        printf("Inge %d crosses to the right. (on bridge: %d)\n", id, on_bridge);
    // Simulate time crossing
    sleep(randint(1,3));
    // Exit bridge
    exit_bridge();
    printf("Inge %d exits bridge. (on bridge: %d)\n", id, on_bridge);
    total_students++;
    return NULL;
}