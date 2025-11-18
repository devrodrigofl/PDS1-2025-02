#include <stdio.h>

int soma(int n) {
    int resultado = n;
    for(int i = 1; i < n; i++)  {
        resultado += i;
    } return resultado;
  /*   int i = 1;
     int soma = n;
     while (i < n)  {
        soma += i;
        i++;
     }
     return soma;
     */
}
    

int main()  {

    printf("%d\n", soma(10));

    return 0;
}