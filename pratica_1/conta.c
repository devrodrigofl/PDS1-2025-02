#include <stdio.h>

int main() {
    float saldo = 0;
    float mes1 = 789.54, mes2 = 303.20, mes3 = -58.25;
    saldo = ((((mes1 * 1.0056)+ mes2) * 1.0056)+ mes3)* 1.0056;
    printf("%.2f\n", saldo);
    return 0;
}