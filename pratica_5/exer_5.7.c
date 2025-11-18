#include <stdio.h>

unsigned int soma_divisores(unsigned int n) {
    int soma = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) soma += i;
    }
    return soma;
}

int main()  {

    printf("%lld\n", soma_divisores(6));

    return 0;
}