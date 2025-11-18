#include <stdio.h>

unsigned long long fatorial(int n) {
    unsigned long long resultado = 1;
    for(int i = 1; i <= n ; i++) {
        resultado = resultado * i;
    }
    return resultado;
}

unsigned long long fatorial(int n) {
    unsigned long long resultado = 1;
    while (n > 1) {
        resultado = resultado * n;
        n--;
    }   
    return resultado;
}

int main()  {

    printf("%lld\n", fatorial(6));

    return 0;
}