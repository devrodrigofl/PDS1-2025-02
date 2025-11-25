#include <stdio.h>

int menorElemento(int v[], int n) {
    if(n == 0) return v[0];
    if(v[n - 1] < menorElemento(v, n - 1)) return v[n - 1];
}