#include <stdio.h>

int main() {
    FILE* arquivo = fopen("case.txt", "r");
    int inicio_intervalo = 0, fim_intervalo = 0, passo = 0;
    fscanf(arquivo, "%d %d %d", &inicio_intervalo, &fim_intervalo, &passo);
    for(int i = inicio_intervalo; i <= fim_intervalo; i += passo) {
        printf("%d %d %d\n", i, ((i*9)/5) + 32, i + 273);
    }
    return 0;
}