#include <stdio.h>
#include <string.h>

int contaocorrencias(char *A, int tam1, char c) {
    int contagem = 0;
    for(int i = 0; i < tam1; i++) {
        if(A[i] == c) contagem++;
    }
    return contagem;
}

int main()  {

    char A[100];
    fgets(A, sizeof(A), stdin);
    int tam1 = strlen(A);
    char c;
    scanf("%c", &c);
    printf("%d\n", contaocorrencias(A, tam1, c));

    return 0;
}