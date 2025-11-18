#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define TAM_PISTA 30
#define MIN_CARROS 4
#define MAX_CARROS 10

int avancarCarros(int posicoes[], int numCarros) {
    //int RAND_MAX = 2; errei essa linha
    for(int i = 0; i < numCarros; i++) {
        posicoes[i] += (rand() % 3) + 1; //errei essa linha
        if(posicoes[i] >= TAM_PISTA) return 0;
    }
    return 1;
}

void mostrarPista(int posicoes[], int numCarros) {
    char pista[numCarros][TAM_PISTA];
    for(int i = 0; i < numCarros; i++) {
        for(int j = 0; j < TAM_PISTA; j++) {
            if (posicoes[i] == j) pista[i][j] = (65 + i);
            else pista[i][j] = '_';
        }
    }

    for(int i = 0; i < numCarros; i++) {
        for(int j = 0; j < TAM_PISTA; j++) {
            printf("%c", pista[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void calcularPodio(int posicoes[], int numCarros, int podio[3]) {
    int i, j;
    for(i = 0; i < 3; i++) {
        int maxIndex = 0;
        //for(j = 0; j < numCarros; j++) {  //acho que errei aqui
        for(j = 1; j < numCarros; j++) {
        //    if(posicoes[j] > maxIndex) {  //acho que errei aqui
            if(posicoes[j] > posicoes[j-1]) {
                maxIndex = j;
            }
        }
        podio[i] = maxIndex;
        posicoes[maxIndex] = -1;
    }
}

void corrida(int numCarros, int podio[3]) {
    int i, posicoes[MAX_CARROS];
    for(i = 0; i < numCarros; i++) {
        posicoes[i] = 0;
    }
    while(avancarCarros(posicoes, numCarros)) { //erre, passei o vetor posicoes com colchete
        system("clear");
        mostrarPista(posicoes, numCarros); //erre, passei o vetor posicoes com colchete
        usleep(500000);
    }
    calcularPodio(posicoes, numCarros, podio); //errei, passei o vetor posicoes e podio com colchete
    printf("Pódio: 1o = %c, 2o = %c, 3o = %c\n", (podio[0] + 65), (podio[1] + 65), (podio[2] + 65));
}

int main() {
    srand(time(NULL));
    int pontosPorCorrida [] = {5, 3, 1};
    int i, j, numCarros, numCorridas = 5;
    int pontuacao[MAX_CARROS], podio[3];
    numCarros = (rand() % (MAX_CARROS - MIN_CARROS + 1)) + MIN_CARROS; //errei essa linha
    printf("O campeonato terá %d Carros.\n", numCarros);
    usleep(500000);
    for(i = 0; i < numCarros; i++) {
        pontuacao[i] = 0;
    }
    for(i = 0; i < numCorridas; i++) {
        printf("\n---- Corrida %d ----\n\n", i + 1);
        corrida(numCarros, podio); //errei essa linha, passei o vetor com colchete
        usleep(5000000);
        for(int j = 0; j <= 2; j++) {
            pontuacao[podio[j]] = pontosPorCorrida[j];
        }
        printf("Pontuacão do campeonato após corrida %d\n", i + 1);
        for(int j = 0; j < numCarros; j++) {
            printf(" %c: %d\n", (j + 65), pontuacao[j]);
        }
        printf("\n");
    }
    int cmp = 0;
    for(i = 0; i < numCarros; i++) { //errei a incializacao do i
        if(pontuacao[i] > pontuacao[cmp]) cmp = i; //errei a segunda parte do if
    }
    printf("campeão: %c, %d pontos.\n", (cmp + 65), pontuacao[cmp]);
    return 0;
}