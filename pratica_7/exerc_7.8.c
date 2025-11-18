#include <stdio.h>

int main()  {

    int n = 0, m = 0;

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
            printf("%d ", (-1 * matriz[i][j]));
        }
        printf("\n");
    }

    return 0;
}