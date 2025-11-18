#include <stdio.h>

int primo(int n) {
    int divisor = 2;
    if ( n <= 1) return 0;
    while (n / divisor >= divisor)  {
        if (n == divisor) {
            return 1;
        } else if (n % divisor == 0) {
            return 0;
        } else divisor++;
    }
    return 1;
}

int main()  {

    int n;
    scanf("%d", &n);
    printf("%d\n", primo(n));

    return 0;
}