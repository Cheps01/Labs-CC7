#ifndef BRIDGE_H
#define BRIDGE_H

#include <unistd.h>
#include <stdio.h>

#include "threads.h"
#include "utils.h"

extern double total_wait;
extern int total_students;

void *student_cross_bridge(void *arg);

#endif //BRIDGE_H