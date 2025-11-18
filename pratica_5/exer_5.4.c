#include <stdio.h>

int main()  {

    int maior = 0; int menor = 1000;
    for (int i = 1; i <= 15; i++)   {
        int idade = 0;
        scanf("%d", &idade);
        if (idade >= maior) {
            maior = idade;
        } else if ( idade <= menor) {
            menor = idade;
        }
    }
    printf("Maior: %d\nMenor: %d\n", maior, menor);

    return 0;
}