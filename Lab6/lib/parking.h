#ifndef PARKING_H
#define PARKING_H

#include <stdio.h>

#define N 2

extern int parking[N];
extern int pc;               

void set_spot(int id);
void clear_spot(int id);

#endif // PARKING_H