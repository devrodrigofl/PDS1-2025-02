#include <stdio.h>
#include <string.h>

void removechar(char *A, int tam1, char c) {
    for(int i = 0; i < tam1; i++) {
        if(A[i] == c) {
            for(int j = i; j <= tam1; j++) {
                A[j] = A[j + 1];
            }
            break;
        }
    }
}

int main()  {

    char A[100];
    fgets(A, sizeof(A), stdin);
    int tam1 = strlen(A);
    char c;
    scanf("%c", &c);
    removechar(A, tam1, c);
    printf("%s\n", A);

    return 0;
}