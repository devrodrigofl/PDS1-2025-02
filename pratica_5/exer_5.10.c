#include <stdio.h>

int inverte(unsigned int n) {
    int invertido = 0, digito = 0;
    while (n != 0) {
        digito = n % 10;
        invertido = (invertido * 10) + digito;
        n = n / 10;
    }
    return invertido;
}

int main()  {

    printf("%d\n", inverte(8062));

    return 0;
}
