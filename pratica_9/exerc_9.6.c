#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE* arquivo = fopen("case.txt", "r");
    int i = 0, j = 0, n = 0;
    char ordem[100];
    char nomes[100][100];
    memset(nomes, 0, sizeof(nomes));
    memset(ordem, 0, sizeof(ordem));
    while (fgets(nomes[i], 100, arquivo) != NULL) {
        i++;
        if (i >= 100) break;
    }

    fclose(arquivo);

    n = i;

    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(nomes[j], nomes[j+1]) > 0) {
                strcpy(ordem, nomes[j]);
                strcpy(nomes[j], nomes[j+1]);
                strcpy(nomes[j+1], ordem);
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        printf("%s\n", nomes[i]);
    }

    return 0;
}