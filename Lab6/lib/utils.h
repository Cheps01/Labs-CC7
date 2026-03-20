#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int randint(int min, int max);
void display(int arr[], int size);
void thread_log(int id, char *msg);
time_t start_time();
double finish_time(time_t start);

#endif // UTILS_H