#include <stdarg.h>
#include "../os/os.h"
#include "string.h"

// Function to display a string via UART
void PRINT(const char *str, ...) {
    va_list args;
    va_start(args, str);
    char type;
    int ivalue;
    float fvalue;
    char* svalue;
    while (*str) {
        if (*str == '%') {
            type = *(++str);
            if (type == 'd') {
                ivalue = va_arg(args, int);
                uart_itoa(ivalue, svalue);
            } else if (type == 'f') {
                fvalue = (float)va_arg(args, double);
                uart_ftoa(fvalue, svalue);
            }
            while (*svalue) uart_putc(*svalue++);
            str++;
            continue;
        }
        uart_putc(*str++);
    }
    va_end(args);
}
// Function to read string from the user via UART
void READ(char *str, ...) {
    va_list args;
    va_start(args, str);
    char *input;
    uart_gets_input(input, 32);
    if (*str == '%') {  
        str++;
        if (*str == 'd') {
            int *ivalue = va_arg(args, int*);
            *ivalue = uart_atoi(input);
        } else if (*str == 'f') {
            float *fvalue = va_arg(args, float*);
            *fvalue = uart_atof(input);
        }
    }
    va_end(args);
}