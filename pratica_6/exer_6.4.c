#include <stdio.h>
#include <string.h>

void reverso(char *Normal, char *Inverso, int tam1) {
    int i = tam1 - 1;
    for(int j = 0; j < tam1; i--, j++) {
        Inverso[j] = Normal[i];
        Inverso[j + 1] = '\0';
    }
}

int main()  {

    char Normal[51], Inverso[51];
    fgets(Normal, sizeof(Normal), stdin);
    int tam1 = strlen(Normal);
    reverso(Normal, Inverso, tam1);
    printf("%s\n", Inverso);

    return 0;
}