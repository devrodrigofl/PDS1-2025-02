#include <math.h>

float loglcdf(float x, float a, float b)    {
    float flog = 0;
    if(x >= 0) {
       return flog = 1 / (1 + pow((x/a), b));
    } else return 0;
}

int maior(int a, int b) {
    if (a >= b) {
        return a;
    } else if (b < a) {
        return b;
    }
}

void aumentaOsDiferentes(int* end_var1, int* end_var2) {
    if(*end_var1 == *end_var2)  {
        *end_var1 = 0;
        *end_var2 = 0;
    } else {
        int soma = *end_var1 + *end_var2;
        *end_var1 = soma;
        *end_var2 = soma;
    }
}

int codigoDeArea(unsigned int number) {
    return number / 100000000;
}

int parEmImpar(unsigned int number) {
    return number += !(number % 2);
}


int par(unsigned int number) {
    return number % 2 == 0;
}

void divisao(int* end_var1, int* end_var2) {
    int resultado = 0, resto = 0;
    resultado = *end_var1 / *end_var2;
    resto = *end_var1 % *end_var2;
    *end_var1 = resultado;
    *end_var2 = resto;
}

float arredonda(float n) {
    float decimal = n - (int)n;
    float inteiro = (int)n;
    if (decimal < 0.25) {
        return inteiro;
    } else if (decimal < 0.75)  {
        return inteiro + 0.5;
    } else return inteiro + 1;
}

void arredondaNotas(float *endNota1, float *endNota2, float *endNota3) {
    *endNota1 = arredonda(*endNota1);
    *endNota2 = arredonda(*endNota2);
    *endNota3 = arredonda(*endNota3);
}

int hotpo(unsigned int n) {
    if (n % 2 == 0) {
        return n / 2;
    } else return (n * 3) + 1;
}