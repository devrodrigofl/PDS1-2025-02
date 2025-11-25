#include <stdio.h>

double somaRecursiva(int v[], int n) {
    if (n == 0) return 0;
    return v[n - 1] + somaRecursiva(v, n - 1);
}

double mediaVetor(int v[], int n) {
    if (n == 0) return 0;
    return somaRecursiva(v, n) / n;
}