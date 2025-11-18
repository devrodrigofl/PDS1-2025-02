#include <stdio.h>

int main()  {

    float num1 = 0, num2 = 0;
    char  op;

    printf("Digite o primeiro número: ");
    scanf("%f", &num1);

    printf("Digite o operador (+, -, *, /): ");
    scanf(" %c", &op);

    printf("Digite o segundo número: ");
    scanf("%f", &num2);

    switch (op) {
    case '+':
        printf("%.2f %c %.2f = %.2f\n", num1, op, num2, num1 + num2);
        break;
    case '-':
        printf("%.2f %c %.2f = %.2f\n", num1, op, num2, num1 - num2);
        break;
    case '*':
        printf("%.2f %c %.2f = %.2f\n", num1, op, num2, num1 * num2);
        break;
    case '/':
        if(num2 == 0) {
            printf("Erro! Divisão por zero não é permitida.\n");
        } else printf("%.2f %c %.2f = %.2f\n", num1, op, num2, num1 / num2);
        break;
    default: printf("Operador inválido!\n");
        break;
    }

    return 0;
}