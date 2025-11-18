#include <stdio.h>

typedef struct {
  char nome[51], local[51];
  int dia, mes, ano;
} eventos;

int main() {
    int n = 0;
    scanf("%d ", &n);
    eventos dados[n];

    for(int i = 0; i < n; i++) {
        scanf(" %50[^\n]", dados[i].nome);
        scanf(" %50[^\n]", dados[i].local);
        scanf("%d %d %d", &dados[i].dia, &dados[i].mes, &dados[i].ano);
    }

    eventos consulta; 
    scanf("%d %d %d", &consulta.dia, &consulta.mes, &consulta.ano);
    
    int a = 0;

    for(int i = 0; i < n; i++) {
        if((consulta.dia == dados[i].dia) && (consulta.mes == dados[i].mes) && (consulta.ano == dados[i].ano)) {
            printf("%s\n%s\n", dados[i].nome, dados[i].local);
            a++;
        }
    }

    if(!a) printf("Nenhum evento encontrado!\n"); 

    return 0;
}