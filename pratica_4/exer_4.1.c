#include <stdio.h>

int main()  {

    int num1, num2, num3, num4, num5;
    scanf("%d %d %d %d %d", &num1, &num2, &num3, &num4, &num5);

    int maior, menor, div3 = 0;

    maior = num1;
    menor = num1;

    if (num2 > maior) {
        maior = num2;
    } else if (num2 < menor) {
        menor = num2;
    }

    if (num3 > maior)   {
        maior = num3;
    } else if (num3 < menor) {
        menor = num3;
    }  

    if (num4 > maior)   {
        maior = num4;
    } else if (num4 < menor) {
        menor = num4;
    }  

    if (num5 > maior)   {
        maior = num5;
    } else if (num5 < menor) {
        menor = num5;
    }  

    if (num1 % 3 == 0) {
            div3++;
        }
    if (num2 % 3 == 0) {
            div3++;
        }
    if (num3 % 3 == 0) {
            div3++;
        }
    if (num4 % 3 == 0) {
            div3++;
        }
    if (num5 % 3 == 0) {
            div3++;
        }

    printf("Maior: %d\nMenor: %d\nQuantidade de divisiveis por 3: %d\n", maior, menor, div3);

    return 0;
}