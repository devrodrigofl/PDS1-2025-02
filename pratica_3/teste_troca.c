#include <stdio.h>
#include "minhas_funcoes.h"

float testaTroca(float x, float y)   {
    troca(&x, &y);
    printf("%.4f %.4f\n", x, y);
    return 0;
}