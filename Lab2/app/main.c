#include "../lib/stdio.h"

void main() {
    char input[32];
    int num1, num2, sum;
    float fnum1, fnum2, fsum;

    PRINT("   __        __   ___          _____     __         __        __ \n");
    PRINT("  / /  ___ _/ /  |_  |  ____  / ___/__ _/ /_____ __/ /__ ____/ /__  _______ _ \n");
    PRINT(" / /__/ _ `/ _ \\/ __/  /___/ / /__/ _ `/ / __/ // / / _ `/ _  / _ \\/ __/ _ `/ \n");
    PRINT("/____/\\_,_/_.__/____/        \\___/\\_,_/_/\\__/\\_,_/_/\\_,_/\\_,_/\\___/_/  \\_,_/ \n");
    while (1) {
        // PRINT("--------------------------------------\n");
        // PRINT("Ingrese primer numero: ");
        // READ("%d", &num1);
        // PRINT("Ingrese segundo numero: ");
        // READ("%d", &num2);
        // sum = num1 + num2;
        // PRINT("%d + %d = %d \n", num1, num2, sum);

        PRINT("--------------------------------------\n");
        PRINT("Ingrese primer numero decimal: ");
        READ("%f", &fnum1);
        PRINT("Ingrese segundo numero decimal: ");
        READ("%f", &fnum2);
        fsum = fnum1 + fnum2;
        PRINT("%f + %f = %f \n", fnum1, fnum2, fsum);
    }
}