#include "parking.h"
#include "utils.h"

int parking[N];                   // parking spots resource
int pc;                           // parked cars counter

void set_spot(int id) {
    int k = 0;
    while(parking[k]) k++;
    parking[k] = id;
    pc++;
}
void clear_spot(int id) {
    int k = 0;
    while(parking[k] != id) k++;
    parking[k] = 0;
    pc--;
}