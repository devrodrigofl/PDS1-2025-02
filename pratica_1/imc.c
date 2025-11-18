#include <stdio.h>

float imc(float altura, float peso)  {
    float c = peso / (altura * altura);
    return c;
}

int main()  {
    float altura_inicial = 0, peso_inicial = 0, peso_final = 0, delta = 0;

//  brutus
    altura_inicial = 1.84;
    peso_inicial = 122;
    peso_final = peso_inicial;
    
    while(imc(altura_inicial, peso_inicial) > 25) {
        peso_inicial -= 0.1;
        delta = peso_final - peso_inicial;
        if(imc(altura_inicial, peso_inicial) <= 25) {
            printf("%.1f\n", delta);
        } else continue;
    } 

//  olivia
    altura_inicial = 1.76;
    peso_inicial = 45;
    peso_final = peso_inicial;

    while(imc(altura_inicial, peso_inicial) < 18.5) {
        peso_inicial += 0.01;
        delta = peso_inicial - peso_final;
        if(imc(altura_inicial, peso_inicial) >= 18.5) {
            printf("%.1f\n", delta);
        } else continue;
    } 

    return 0;
}
