unsigned int soma1SePar(unsigned int number)    {
    unsigned int result = 0;
    result = (number * !(number % 2 == 0)) + ((number + 1) * (number % 2 == 0));
    return result;
}