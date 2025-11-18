#include <stdio.h>

int main()  {

    int n = 0, m = 0, indice = 0, maior = 0;

    scanf("%d", &n);
    scanf("%d", &m);

    int matriz[n][m];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(matriz[i][j] > maior) {
                maior = matriz[i][j];
                indice = j;
            } else if(matriz[i][j] == maior && j < indice) {
                indice = j;
            }
        }
    }

    printf("%d\n", indice);

    return 0;
}