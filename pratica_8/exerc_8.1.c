#include <stdio.h>
#include <math.h>

typedef struct {
    float EIXO_X;
    float EIXO_Y;
} coordenadas;

int main() {
    coordenadas PAR_COORDENADAS[2];
    for(int i = 0; i < 2; i++) {
        scanf("%f %f", &PAR_COORDENADAS[i].EIXO_X, &PAR_COORDENADAS[i].EIXO_Y);
    }
    float SUB_EIXO_X = pow((PAR_COORDENADAS[1].EIXO_X - PAR_COORDENADAS[0].EIXO_X), 2);
    float SUB_EIXO_Y = pow((PAR_COORDENADAS[1].EIXO_Y - PAR_COORDENADAS[0].EIXO_Y), 2);
    printf("%.2f", sqrt(SUB_EIXO_X + SUB_EIXO_Y));
    return 0;
}