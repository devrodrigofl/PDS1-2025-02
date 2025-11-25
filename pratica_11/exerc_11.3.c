#include <stdio.h>

int somaVetor(int v[], int n) {
    if(n == 0) return 0;
    return v[n - 1] + somaVetor(v, n - 1);
}