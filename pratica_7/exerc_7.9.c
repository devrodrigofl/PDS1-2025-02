#include <stdio.h>

int verificamatrizigual(int na, int ma, int A[na][ma], int nb, int mb, int B[nb][mb]) {
    if(na != nb || ma != mb) return 0;

    for(int i = 0; i < na; i++) {
        for(int j = 0; j < ma; j++) {
            if(A[i][j] != B[i][j]) return 0;
        }
    }

    return 1;
}

int main()  {

    int na = 0, ma = 0, nb = 0, mb = 0;

    scanf("%d", &na);
    scanf("%d", &ma);

    int A[na][ma];

    for(int i = 0; i < na; i++) {
        for(int j = 0; j < ma; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    scanf("%d", &nb);
    scanf("%d", &mb);

    int B[nb][mb];

    for(int i = 0; i < nb; i++) {
        for(int j = 0; j < mb; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    int verifica = verificamatrizigual(na, ma, A, nb, mb, B);
    printf("%d\n", verifica);
    
    return 0;
}