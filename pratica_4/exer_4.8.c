#include <stdio.h>

void par_ou_impar (int num) {
    if (num > 0 && num % 2 == 0) {
        printf("%d e par", num);
    } else if (num > 0 && num % 2 != 0) {
        printf("%d e impar", num);
    } else printf("ERRO: numero invalido");
}