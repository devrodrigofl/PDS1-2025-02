#include <stdio.h>
#include <math.h>

int inverteNumero(int x) {
    if(x < 10) return x;
    return((x % 10) * pow(10, ((int)log10(x / 10) + 1)) + inverteNumero(x / 10));
}