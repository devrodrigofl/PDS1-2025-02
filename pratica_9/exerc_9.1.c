#include <stdio.h>
#include <string.h>

int main() {
    FILE* arquivo = fopen("texto.txt", "r");
    int linha_atual = 0, linha_max = 0, i = 0;
    char linha[100], maior_linha[100];
    memset(linha, 0, sizeof(linha));
    memset(maior_linha, 0, sizeof(maior_linha));
    while(!feof(arquivo)) {
        fscanf(arquivo, "%c", &linha[i]);
        linha_atual++;
        if(linha[i] == '\n') {
            if(linha_atual > linha_max) {
                linha_max = linha_atual;
                strcpy(maior_linha, linha);
            } 
            i = 0;
            linha_atual = 0;
        }
        else i++;
    }
    printf("%s\n%d\n", maior_linha, linha_max);
    return 0;
}