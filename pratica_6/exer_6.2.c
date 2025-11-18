#include <stdio.h>
#include <string.h>

void concatena(char *A, int tam1, char *B, int tam2, char *S) {
    strcat(A, B);
    strcpy(S, A);
}

int main()  {

    char A[21] = "123", B[21] = "456", S[41];
    //fgets(A, sizeof(A), stdin);
    //fgets(B, sizeof(B), stdin);
    int tam1 = strlen(A), tam2 = strlen(B);
    concatena(A, tam1, B, tam2, S);
    printf("%s\n", S);

    return 0;
}