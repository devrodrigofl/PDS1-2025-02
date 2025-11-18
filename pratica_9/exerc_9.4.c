#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int primo(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return 0; 
    }
    return 1;
}

int main() {
    FILE* arquivo = fopen("case.txt", "r");
    int i = 0, soma = 0, maior = 0, menor = 0, n_primos = 0;
    float media_pares = 0;
    char str[100][100];
    int num[100];
    memset(str, 0, sizeof(str));
    memset(num, 0, sizeof(num));

    while (fgets(str[i], 100, arquivo) != NULL) {
        num[i] = atoi(str[i]);
        i++;
        if (i >= 100) break;
    }
    
    fclose(arquivo);
    
    int n = i, media = 0;
    menor = num[0];

    for(i = 0; i < n; i++) {
        soma += num[i];
        if(num[i] > maior) maior = num[i];
        if(num[i] < menor) menor = num[i];
        if(num[i] % 2 == 0) {
            media_pares += num[i];
            media++;
        }
        if(primo(num[i])) n_primos++;
    }

    printf("A soma é: %d\n", soma);
    printf("O maior número é: %d\n", maior);
    printf("O menor número é: %d\n", menor);
    printf("A média dos pares é: %.2f\n", (media_pares / media));
    printf("O número de primos é: %d\n", n_primos);
    
    return 0;
}