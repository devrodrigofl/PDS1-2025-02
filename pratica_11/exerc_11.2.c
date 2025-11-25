#include <stdio.h>

int somaCubos(int n) {
    int soma = 0;
    if(n == 1) return n * n * n;
    if(n > 1) {
       soma += (n * n * n) + somaCubos(n - 1);
    }
    return soma;
}