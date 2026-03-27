#include "utils.h"

int randint(int min, int max) {
    int rd_num = rand() % (max - min + 1) + min;
    return rd_num;
}
time_t start_timer() {
    time_t start;
    time(&start);
    return start;
}
double end_timer(time_t start) {
    time_t end;
    time(&end);
    return difftime(end, start);
}