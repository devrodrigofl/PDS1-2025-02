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

    float mais_velho = x[0].idade;
    char velho[20];
    strcpy(velho, x[0].nome);

    for(int i = 0; i < 4; i++) {
        for(int j = i + 1; j < 5; j++) {
            if(x[j].idade > x[i].idade) {
                atleta troca = x[i];
                x[i] = x[j];
                x[j] = troca;    
            }
        }
    }

    for(int i = 0; i < 5; i++) {
        printf("%d- %s\n", i + 1, x[i].nome);
    }

    return 0;
}