unsigned long long fast_pow_2(int expoente) {
    unsigned long long potencia = 1;
    potencia = potencia << expoente;
    return potencia;
}