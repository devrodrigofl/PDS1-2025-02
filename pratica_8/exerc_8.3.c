#include <stdio.h>

typedef struct {
    float EIXO_X;
    float EIXO_Y;
} coordenadas;

int main() {
    coordenadas PAR_COORDENADAS[3];

    for(int i = 0; i < 3; i++) {
        scanf("%f %f", &PAR_COORDENADAS[i].EIXO_X, &PAR_COORDENADAS[i].EIXO_Y);
        if(i == 1) {
            while((PAR_COORDENADAS[1].EIXO_X <= PAR_COORDENADAS[0].EIXO_X) || (PAR_COORDENADAS[1].EIXO_Y >= PAR_COORDENADAS[0].EIXO_Y)) {
                printf("Coordenada Invalida\n");
                scanf("%f %f", &PAR_COORDENADAS[1].EIXO_X, &PAR_COORDENADAS[1].EIXO_Y);
            }
        }
    }

    int pertence = 0;

    if(PAR_COORDENADAS[2].EIXO_X <= PAR_COORDENADAS[1].EIXO_X && PAR_COORDENADAS[2].EIXO_X >= PAR_COORDENADAS[0].EIXO_X) pertence += 1;
    if(PAR_COORDENADAS[2].EIXO_Y >= PAR_COORDENADAS[1].EIXO_Y && PAR_COORDENADAS[2].EIXO_Y <= PAR_COORDENADAS[0].EIXO_Y) pertence += 1;
    if(pertence == 2) {
        printf("O ponto pertence ao retangulo\n");
    } else printf("O ponto nao pertence ao retangulo\n");

    return 0;
}