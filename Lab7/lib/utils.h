#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdlib.h>

int randint(int min, int max);
time_t start_timer();
double end_timer(time_t start);

#endif // UTILS_H