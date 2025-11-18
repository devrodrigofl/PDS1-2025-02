#include <stdio.h>
#include <string.h>

int main()  {

    int limite = 0;
    do {scanf("%d", &limite);} while(limite < 12); 

    int soma_maxima = 2000001;
    int soma_de_cubos[soma_maxima];
    memset(soma_de_cubos, 0, sizeof(soma_de_cubos));

    for(int i = 1; i <= limite; i++) {
        for(int j = i + 1; j <= limite; j++) {
            int soma = i*i*i + j*j*j;
            if(soma >= soma_maxima) continue;
            if(soma_de_cubos[soma] != 0) {
                printf("%d tem uma soma de dois cubos de duas maneiras distintas\n", soma);
            } else soma_de_cubos[soma] = i;
        }
    }

    return 0;
}

