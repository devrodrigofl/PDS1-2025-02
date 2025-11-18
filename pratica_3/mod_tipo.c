#include <stdio.h>

int main()  {

    long long menor = 1;
    unsigned long long maior = 0;
    menor = menor << 63;
    printf("menor: %lld\nmaior: %llu\n", menor, ~maior);

    return 0;
}