#include <stdio.h>

int populacao(unsigned long habitantes_a, double taxa_a, unsigned long habitantes_b, double taxa_b) {
    int anos = 0;
    taxa_a = 1 + (taxa_a / 100);
    taxa_b = 1 + (taxa_b / 100);
    for(anos ; habitantes_a < habitantes_b; anos++)    {
        habitantes_a = habitantes_a * taxa_a;
        habitantes_b = habitantes_b * taxa_b;
    } return anos;
}

int main()  {

    printf("%d", populacao(80000, 3, 200000, 1.5));

    return 0;
}