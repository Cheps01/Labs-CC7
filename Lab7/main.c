#include <stdio.h>
#include "threads.h"
#include "bridge.h"

#define THREADS 10

int main() {
    init_threads(THREADS, student_cross_bridge);
    printf("-------------------------------------------\n");
    printf("Total students crossed: %d\n", total_students);
    printf("Average waiting time: %f\n", (double)(total_wait / total_students));
    return 0;
}