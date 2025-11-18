#include <stdio.h>
#include <string.h>

typedef struct {
  char nome[20], esporte[20];
  int idade;
  float altura;
} atleta;

int main() {
    atleta x[5];

    for(int i = 0; i < 5; i++) {
        scanf("%19s %19s %d %f", x[i].nome, x[i].esporte, &x[i].idade, &x[i].altura);
    }

    float maior_altura = x[0].altura;
    char alto[20];
    strcpy(alto, x[0].nome);
    float mais_velho = x[0].idade;
    char velho[20];
    strcpy(velho, x[0].nome);

    for(int i = 1; i < 5; i++) {
        if(x[i].altura > maior_altura) {
            maior_altura = x[i].altura;
            strcpy(alto, x[i].nome);
        }
        if(x[i].idade > mais_velho) {
            mais_velho = x[i].idade;
            strcpy(velho, x[i].nome);
        }
    }

    printf("Mais alto: %s\nMais velho: %s\n", alto, velho);
    
    return 0;
}