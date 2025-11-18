#include <stdio.h>
#include <string.h>

int main()  {

    int n = 0, troca = 0;

    scanf("%d", &n);
    int A[n];
    memset(A, 0, n * 4);
    for(int i = 0; i < n; i++) {
        scanf("%d", &A[i]); 
    }

    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(A[i] < A[j]) {
            troca = A[i];
            A[i] = A[j];
            A[j] = troca;
            }
        }
        printf("%d ", A[i]);
    }
    
    return 0;
}