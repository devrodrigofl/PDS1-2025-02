#include <stdio.h>
#include <string.h>

int palavras(char *A, int tam1) {
    int contagem = 1;
    for(int i = 0; i <= tam1; i++) {
        if(A[i] == ' ') contagem++;
    }
    return contagem;
}

int palavras2(char *A, int tam1) {
    int contagem = 1;
    for(int i = 0; i <= tam1; i++) {
        if(A[i] == ' ') contagem++;
    }
    if(A[0] == ' ') contagem--;
    if(A[tam1 - 1] == ' ') contagem--;
    
    return contagem;
}

int main()  {

    char A[51];
    fgets(A, sizeof(A), stdin);
    int tam1 = strlen(A) - 1;
    printf("%d\n", palavras(A, tam1));
    printf("%d\n", palavras2(A, tam1));

    return 0;
}