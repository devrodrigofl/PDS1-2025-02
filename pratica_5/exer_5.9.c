#include <stdio.h>

int soma_digitos_pares (unsigned int n) {
    int soma = 0, digito = 0;
    while (n > 0) {
        digito = n % 10;
        if (digito % 2 == 0) {
            soma += digito;
        }
        n /= 10;
    }
    return soma;
}

int soma_digitos_pares (unsigned int n) {
    int soma = 0, div = 10;
    while ((n / div) >= 1) {
        if ((n / div) < 10 && (n / div) % 2 == 0) {
            soma = soma + (n / div);
        }
        if ((((n % div) - (n % (div / 10))) / (div / 10)) % 2 == 0) {
            soma = soma + (((n % div) - (n % (div / 10))) / (div / 10));
        } 
        div = div * 10;
    }
    return soma;
}

int soma_digitos_pares (unsigned int n) {
    int soma = 0, div = 10;
    while ((n / div) >= 1) {
        if ((n / div) < 10 && (n / div) % 2 == 0) {
            soma = soma + (n / div);
        }
        if (((n % div) - (n % (div / 10))) % 2 == 0 && (n % div) < 10) {
            soma = soma + ((n % div) - (n % (div / 10)));
        } else if ((((n % div) - (n % (div / 10))) / (div / 10)) % 2 == 0) {
            soma = soma + (((n % div) - (n % (div / 10))) / (div / 10));
        } 
        div = div * 10;
    }
    return soma;
}

int soma_digitos_pares (unsigned int n) {
    int soma = 0, div = 10;
    while ((n / div) >= 1) {
        printf("%d %d %d %d\n", soma, div, n, 0);
        if ((n / div) < 10 && (n / div) % 2 == 0) {
            printf("%d %d %d %d\n", soma, div, n, 1);
            soma = soma + (n / div);
            printf("%d %d %d %d\n", soma, div, n, 1);
        }
        if (((n % div) - (n % (div / 10))) % 2 == 0 && (n % div) < 10) {
            printf("%d %d %d %d\n", soma, div, n, 2);
            soma = soma + ((n % div) - (n % (div / 10)));
            printf("%d %d %d %d\n", soma, div, n, 2);
        } else if ((((n % div) - (n % (div / 10))) / (div / 10)) % 2 == 0) {
            printf("%d %d %d %d\n", soma, div, n, 3);
            soma = soma + (((n % div) - (n % (div / 10))) / (div / 10));
            printf("%d %d %d %d\n", soma, div, n, 3);
        } 
        div = div * 10;
        printf("%d %d %d %d\n", soma, div, n, 4);
    }
    return soma;
}

int main()  {

    printf("%d\n", soma_digitos_pares(8062));

    return 0;
}
