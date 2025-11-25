#include <stdio.h>

void imprimeNaturais(int N) {
    if(N == 0) printf("%d", N);
    if(N > 0) {
        printf("%d\n", N);
        imprimeNaturais(N - 1);
    }
}