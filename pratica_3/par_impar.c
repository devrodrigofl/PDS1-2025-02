int parOuImpar(unsigned int number) {
    unsigned int result = 0;
    result = number % 2 == 0;
    return result;
}

int parOuImpar(unsigned int number) {
    return !(number & 1);
}