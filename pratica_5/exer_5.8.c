#include <stdio.h>

int mdc(int a, int b) {
    int multiplicaPrimo = 1, divisor = 2;
    for (int i = 2; i <= a && i <= b; i++) {
        while (i / divisor >= divisor)  {
            if (i == divisor) {
                break;
            } else divisor++;
        }
        while (a % i == 0 && b % i == 0) {
            multiplicaPrimo = multiplicaPrimo * i;
            a = a / i;
            b = b / i;
        }
    }
    return multiplicaPrimo;
}

int main()  {

    printf("%d\n", mdc(27, 18));

    return 0;
}