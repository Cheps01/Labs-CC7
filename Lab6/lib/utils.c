#include "utils.h"

int randint(int min, int max) {
    int rd_num = rand() % (max - min + 1) + min;
    return rd_num;
}
void display(int arr[], int size) {
    printf("Parking lot: [");
    for (int i=0; i<size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}
void thread_log(int id, char *msg) {
    time_t curtime;
    time(&curtime);
    char *time_stamp = ctime(&curtime);
    time_stamp[24] = '\0';
    printf("[%s] Car %d: %s", time_stamp, id, msg);
}
time_t start_time() {
    time_t start;
    start = time(NULL);
    return start; 
}
double finish_time(time_t start) {
    time_t end;
    end = time(NULL);
    return ((double) end - start);
}