#include <stdio.h>

int main()  {

    int limite_direito = 0, limite_inferior = 0, limite_superior = 0, limite_esquerdo = 0;
    int n = 0, m = 0;
    
    scanf("%d", &n);
    scanf("%d", &m);

    int A[n][m];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    int linha = 0;
    int coluna = 0;
    int limite = 0;
    int numero = n * m;
    int diminui = 2;

    limite_inferior = n - 1;
    limite_direito = m - 1;
    

    while(limite < (numero)) {

        while(coluna < limite_direito) {
            printf("%d ", A[linha][coluna]);
            coluna++;
            limite++;
            if(limite == (numero)) break;
        } limite_superior++;

        if(limite == (numero)) break;

        while(linha < limite_inferior) {
            printf("%d ", A[linha][coluna]);
            linha++;
            limite++;
            if(limite == (numero)) break;
        } limite_direito--;

        if(limite == (numero)) break;

        while(coluna > limite_esquerdo) {
            printf("%d ", A[linha][coluna]);
            coluna--;
            limite++;
            if(limite == (numero)) break;
        } 
        
        limite_inferior = n - diminui;
        diminui++;

        if(limite == (numero)) break;

        while(linha > limite_superior) {
            printf("%d ", A[linha][coluna]);
            linha--;
            limite++;
            if(limite == (numero)) break;
        } limite_esquerdo++;

    }

    return 0;
}