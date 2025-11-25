#include <stdio.h>
#include <string.h>

struct lutador {
char *nome;
int vitalidade;
int dano_maximo;
};
typedef struct lutador Lutador;

int randint(int min, int max) {
return min + rand()%(max-min+1);
}

Lutador* carrega_lutadores(int *n) {
    FILE* arquivo = fopen("lutadores.txt", 'r');
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }
    fscanf(arquivo, "%d", n);
    Lutador* vetor = (Lutador*)malloc(*n * sizeof(Lutador));
    if (vetor == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }
    for(int i = 0; i < n; i++) {
        vetor[i].nome = (char*)malloc(10 * sizeof(char));
        fscanf(arquivo, "%s %d %d", vetor[i].nome, vetor[i].vitalidade, vetor[i].dano_maximo);
    }
    fclose(arquivo);
    return vetor;
}

void ataque(Lutador atacante, Lutador* alvo) {
    int dano = randint(1, atacante.dano_maximo);
    alvo->vitalidade -= dano;
    if(alvo->vitalidade < 0) alvo->vitalidade = 0;
}

int main() {
srand(time(NULL));
char resp;
do {
batalha();
printf("\nDe novo? (S/N)");
fflush(stdin);
resp = getchar();
} while(toupper(resp) == 'S');
return 0;
}