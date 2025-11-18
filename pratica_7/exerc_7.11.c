#include <stdio.h>
#include <stdlib.h>

void preencherpseudoaleatoriamente(int seed, int inferior, int superior, int n, int m, int A[n][m]) {
    srand(seed);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            A[i][j] = (inferior + (rand() % (superior - inferior)));
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int main()  {

    int seed = 0, limite_inferior = 0, limite_superior = 0, n = 0, m = 0;

    scanf("%d", &seed);
    scanf("%d", &limite_inferior);
    scanf("%d", &limite_superior);
    scanf("%d", &n);
    scanf("%d", &m);

    int A[n][m];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            A[i][j] = 0;
        }
    }
    
    preencherpseudoaleatoriamente(seed, limite_inferior, limite_superior, n, m, A);

    return 0;
}