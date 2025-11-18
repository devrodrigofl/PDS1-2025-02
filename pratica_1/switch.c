#include <stdio.h>

void main() {
    float a = 3.14159, b = 2.71828;
    float c = a, d = b;
    a = d;
    b = c;

    printf("\nPi = %f", b);
    printf("\nEuler = %f", a);
}