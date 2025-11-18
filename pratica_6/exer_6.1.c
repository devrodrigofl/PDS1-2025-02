#include <stdio.h>
#include <string.h>

int contacarateresalfa(char* A, int tam) {
    int alfa = 0;
    for(int i = 0; i <= tam; i++) {
        if(A[i] >= 'a' && A[i] <= 'z') {
            alfa++;
        } else if(A[i] >= 'A' && A[i] <= 'Z') {
            alfa++;
        } else if(A[i] >= '0' && A[i] <= '9') {
            alfa++;
        }
    }
    return alfa;
}

int main()  {

    char A[21];
    fgets(A, sizeof(A), stdin);
    int tam = strlen(A);
    printf("%s %d\n", A, tam);
    printf("%d\n", contacarateresalfa(A, tam));

    return 0;
}