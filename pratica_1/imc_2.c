#include <stdio.h>

int main()  {

    float imc_minimo = 18.5, imc_maximo = 25;

//  brutus
    float altura_b = 1.84, peso_b = 122;
    float peso_maximo = altura_b * altura_b * imc_maximo;
    printf("%.1f ", peso_b - peso_maximo);

//  olivia
    float altura_o = 1.76, peso_o = 45;
    float peso_minino = altura_o * altura_o * imc_minimo;
    printf("%.1f\n", peso_minino - peso_o);

    return 0;
}