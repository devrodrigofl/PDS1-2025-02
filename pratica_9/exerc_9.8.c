#include <stdio.h>
#include <string.h> 

int main() {
    FILE* arquivo = fopen("datas.txt", "r");

    int data[100][3];
    char linha_do_arquivo[100];
    int i = 0;

    while (fgets(linha_do_arquivo, 100, arquivo) != NULL) {
        sscanf(linha_do_arquivo, "%d/%d/%d", 
               &data[i][0], 
               &data[i][1], 
               &data[i][2]);
        i++;
        if (i >= 100) break;
    }
    fclose(arquivo);

    int tamanho = i;

    int dia_recente = data[0][0];
    int mes_recente = data[0][1];
    int ano_recente = data[0][2];

    for(i = 1; i < tamanho; i++) {
        
        int dia_atual = data[i][0];
        int mes_atual = data[i][1];
        int ano_atual = data[i][2];

        if (ano_atual > ano_recente) {
            ano_recente = ano_atual;
            mes_recente = mes_atual;
            dia_recente = dia_atual;
        } 
        else if (ano_atual == ano_recente && mes_atual > mes_recente) {
            mes_recente = mes_atual;
            dia_recente = dia_atual;
        }
        else if (ano_atual == ano_recente && mes_atual == mes_recente && dia_atual > dia_recente) {
            dia_recente = dia_atual;
        }
    }

    printf("%02d/%02d/%d\n", dia_recente, mes_recente, ano_recente);

    return 0;
}