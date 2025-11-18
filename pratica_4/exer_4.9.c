#include <stdio.h>

int main()  {

    int ano = 0;
    printf("Digite um ano: ");
    scanf("%d", &ano);

    if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
        printf("O ano de %d e bissexto.\n", ano);
    } else if (ano % 4 != 0 || ano % 100 == 0) {
        printf("O ano de %d nao e bissexto.\n", ano);
    }

    return 0;
}