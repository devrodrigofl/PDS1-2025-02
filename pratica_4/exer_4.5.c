#include <stdio.h>

int main()  {

    int dia = 0, mes = 0, ano = 0;
    scanf("%d %d %d", &dia, &mes, &ano);

    if (ano >= 0) {
        switch (mes) {
        case 1:
            if (dia >= 1 && dia <= 31) {
            printf("Data valida\n");
            } else printf("Data invalida\n");
            break;
        case 2:
            if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
                if (dia >= 1 && dia <= 29) {
                printf("Data valida\n");
                } else printf("Data invalida\n");
            } else if (ano % 4 != 0 || ano % 100 == 0) {
                if (dia >= 1 && dia <= 28) {
                printf("Data valida\n");
                } else printf("Data invalida\n");
            } else printf("Data invalida\n");
            break;
        case 3:
            if (dia >= 1 && dia <= 31) {
            printf("Data valida\n");
            } else printf("Data invalida\n");
            break;
        case 4:
            if (dia >= 1 && dia <= 30) {
            printf("Data valida\n");
            } else printf("Data invalida\n");
            break;
        case 5:
            if (dia >= 1 && dia <= 31) {
            printf("Data valida\n");
            } else printf("Data invalida\n");
            break;
        case 6:
            if (dia >= 1 && dia <= 30) {
            printf("Data valida\n");
            } else printf("Data invalida\n");
            break;
        case 7:
            if (dia >= 1 && dia <= 31) {
            printf("Data valida\n");
            } else printf("Data invalida\n");
            break;
        case 8:
            if (dia >= 1 && dia <= 31) {
            printf("Data valida\n");
            } else printf("Data invalida\n");
            break;
        case 9:
            if (dia >= 1 && dia <= 30) {
            printf("Data valida\n");
            } else printf("Data invalida\n");
            break;
        case 10:
            if (dia >= 1 && dia <= 31) {
            printf("Data valida\n");
            } else printf("Data invalida\n");
            break;
        case 11:
            if (dia >= 1 && dia <= 30) {
            printf("Data valida\n");
            } else printf("Data invalida\n");
            break;
        case 12:
            if (dia >= 1 && dia <= 31) {
            printf("Data valida\n");
            } else printf("Data invalida\n");
            break;  
        default:
            printf("Data invalida\n");
            break;
        }
    } else printf("Data invalida\n");

    return 0;
}