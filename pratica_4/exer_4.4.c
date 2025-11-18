#include <stdio.h>

int main()  {

    float price = 0;
    char state;
    scanf("%f %c", &price, &state);

    switch (state) {
    case 'G':
        printf("O valor em MG seria de R$%.2f\n", price * 1.07);
        break;
    case 'P':
        printf("O valor em SP seria de R$%.2f\n", price * 1.12);
        break;
    case 'J':
        printf("O valor em RJ seria de R$%.2f\n", price * 1.15);
        break;
    case 'S':
        printf("O valor em MS seria de R$%.2f\n", price * 1.08);
        break;
    default:
        printf("Estado invalido\n");
        break;
    }

    return 0;
}