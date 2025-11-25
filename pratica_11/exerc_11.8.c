#include <stdio.h>

void imprimeBinario(int n) {
    if(n <= 0) printf("%d", 0);
    else {
        imprimeBinario(n / 2);
        printf("%d", n % 2);
    }
}