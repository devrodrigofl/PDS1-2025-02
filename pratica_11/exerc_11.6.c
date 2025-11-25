#include <stdio.h>

void imprimeInvertida(char str[]) {
    if (str[0] == '\0') return;
    imprimeInvertida(str + 1);
    printf("%c", str[0]);
}