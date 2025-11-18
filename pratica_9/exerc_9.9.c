#include <stdio.h>

int main() {
    FILE* arquivo = fopen("notas.txt", "r");

    char nome[51];
    int n1, n2, n3, n4;
    float media;

    while (fscanf(arquivo, "%s %d %d %d %d", nome, &n1, &n2, &n3, &n4) == 5) {
        
        media = (n1 + n2 + n3 + n4) / 4.0;

        if (media >= 60.0) {
            printf("Nome: %s - Média: %.2f\n", nome, media);
        }
    }

    fclose(arquivo);

    return 0;
}