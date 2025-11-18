#include <stdio.h>
#define TAMANHO (4)

void tabuleiro_input(int tabuleiro[TAMANHO][TAMANHO])    {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            scanf("%d", &tabuleiro[i][j]);
        }
    }
    printf("\n");
}

void tabuleiro_output(int tabuleiro[TAMANHO][TAMANHO])    {
    for(int i = 0; i < TAMANHO; i++) {
        for(int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int min(int x, int y){
    if(x < y) {
        return x;
    } else return y;
    return 0;
}

int q1(int tabuleiro[TAMANHO][TAMANHO])     {
    for(int i = 0; i < TAMANHO; i++) {
        int linha_minimo = 0;
        for(int j = 0; j < TAMANHO; j++) {
            if(tabuleiro[i][j] == 1)    {
                linha_minimo = 1;
                break;
            }
        }
        if(!linha_minimo)   {
            return 0;
        }       
    }
    return 1;
}

int q2(int tabuleiro[TAMANHO][TAMANHO])     {
    for(int i = 0; i < TAMANHO; i++)    {
        for(int j = 0; j < TAMANHO - 1; j++)    {
            for(int k = j + 1; k < TAMANHO; k++)    {
                if((!tabuleiro[i][j] || !tabuleiro[i][k]) == 1) {
                    break;
                } else return 0;
            }
            for(int k = j + 2; k < TAMANHO; k++)    {
                if((!tabuleiro[i][j] || !tabuleiro[i][k]) == 1) {
                    break;
                } else return 0;
            }
        }
    }
    return 1;
}

int q3(int tabuleiro[TAMANHO][TAMANHO])     {
    for(int j = 0; j < TAMANHO; j++)    {
        for(int i = 0; i < TAMANHO - 1; i++)    {
            for(int k = i + 1; k < TAMANHO; k++)    {
                if((!tabuleiro[i][j] || !tabuleiro[k][j]) == 1) {
                    break;
                } else return 0;
            }
            for(int k = i + 2; k < TAMANHO; k++)    {
                if((!tabuleiro[i][j] || !tabuleiro[k][j]) == 1) {
                    break;
                } else return 0;
            }
        }
    }
    return 1;
}

int q4(int tabuleiro[TAMANHO][TAMANHO])     {
    for(int i = 1; i < TAMANHO; i++)    {
        for(int j = 0; j < TAMANHO - 1; j++)    {
            for(int k = 0; k < min(i - 1, TAMANHO - j); k++)    {
                if((!tabuleiro[i][j] || !tabuleiro[i-k][k+j]) == 1) {
                    break;
                } else return 0;
            }
            for(int k = 1; k < min(i - 1, TAMANHO - j); k++)    {
                if((!tabuleiro[i][j] || !tabuleiro[i-k][k+j]) == 1) {
                    break;
                } else return 0;
            }
        }
    }
    return 1;
}

int q5(int tabuleiro[TAMANHO][TAMANHO])     {
    for(int i = 0; i < TAMANHO - 1; i++)    {
        for(int j = 0; j < TAMANHO - 1; j++)    {
            for(int k = 0; k < min(TAMANHO - 1, TAMANHO - j); k++)    {
                if((!tabuleiro[i][j] || !tabuleiro[i+k][j+k]) == 1) {
                    break;
                } else return 0;
            }
            for(int k = 1; k < min(i - 1, TAMANHO - j); k++)    {
                if((!tabuleiro[i][j] || !tabuleiro[i+k][j+k]) == 1) {
                    break;
                } else return 0;
            }
        }
    }
    return 1;
}

int main()  {

    
    int tabuleiro[TAMANHO][TAMANHO];
    tabuleiro_input(tabuleiro);
    tabuleiro_output(tabuleiro);

    if(q1(tabuleiro))   {
        printf("\nq1 satisfeito\n");
    } 
    else {
        printf("q1 não satisfeito\n");
    }

    if(q2(tabuleiro))   {
        printf("q2 satisfeito\n");
    } 
    else {
        printf("q2 não satisfeito\n");
    }

    if(q3(tabuleiro))   {
        printf("q3 satisfeito\n");
    } 
    else {
        printf("q3 não satisfeito\n");
    }

    if(q4(tabuleiro))   {
        printf("q4 satisfeito\n");
    } 
    else {
        printf("q4 não satisfeito\n");
    }

    if(q5(tabuleiro))   {
        printf("q5 satisfeito\n");
    } 
    else {
        printf("q5 não satisfeito\n");
    }

    return 0;
}

