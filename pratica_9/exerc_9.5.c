#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE* arquivo = fopen("case.txt", "r");
    int i = 0, j = 0, maior = 0, menor = 200, nome_velho = 0, nome_novo = 0;
    char nomes[100][100];
    int num[100];
    memset(nomes, 0, sizeof(nomes));
    memset(num, 0, sizeof(num));

    while (fgets(nomes[i], 100, arquivo) != NULL) {
        if(i % 2 != 0) {
            num[j] = atoi(nomes[i]);
            j++;
        }
        i++;
        if (i >= 100) break;
    }

    fclose(arquivo);

    for(i = 0; i < j; i++) {
        if(num[i] > maior) {
            maior = num[i];
            nome_velho = i;
        }
        if(num[i] < menor) {
            menor = num[i];
            nome_novo = i;
        }
    }
    
    printf("%s%s", nomes[nome_novo * 2], nomes[nome_velho * 2]);
    
    return 0;
}