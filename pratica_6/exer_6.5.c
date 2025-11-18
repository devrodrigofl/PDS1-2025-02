#include <stdio.h>
#include <string.h>

int main()  {

    char A[51], B[51];
    fgets(A, sizeof(A), stdin);
    fgets(B, sizeof(B), stdin);
    int tam1 = strlen(A), tam2 = strlen(B);
    int teste = 0;

    if(tam2 > tam1) {
        printf("Nao e substring\n");
        return 0;
    }

    for(int i = 0; i <= tam1 - tam2; i++) {
        teste = 1;
        for(int j = 0; j < tam2 - 1; j++) {
            if(B[j] != A[i + j]) {
                teste = 0;
                break;
            }
        }
        if(teste) break;
    }
    
    if(teste) printf("E substring\n");
    else printf("Nao e substring\n");


    return 0;
}