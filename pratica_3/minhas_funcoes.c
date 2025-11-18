void soma1(int *valor)   {
    *valor += 1;
}

void troca(float *end_valor1, float *end_valor2)  {
    float change = *end_valor1;
    *end_valor1 = *end_valor2;
    *end_valor2 = change;
}

int ddd(long long numero)   {
    numero = numero / 1000000000;
    return numero;
}