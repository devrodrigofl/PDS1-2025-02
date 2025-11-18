#include <stdio.h>
#include <string.h> 

int main() {
    FILE* arquivo = fopen("texto.txt", "r");

    int tamanho = 0;
    scanf("%d", &tamanho);

    char palavra[100];

    while (fscanf(arquivo, "%s", palavra) == 1) {

        if (strlen(palavra) >= tamanho) {
            printf("%s\n", palavra);
        }
    }

    fclose(arquivo);
    
    return 0;
}