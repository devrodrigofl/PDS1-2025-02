#include <stdio.h>
#include <string.h>
  
float calculamedia(int n, float vetor[]) {
    float media = 0;
    int i = 0;
    for(i = 0; i < n; i++) {
        media += vetor[i];
    }
    media /= i;
}

int main()  {

    int n = 0;
    scanf("%d", &n);
    int vtr[n];
    memset(vtr, 0, n * 4);

    for(int i = 0; i < n; i++) {
        scanf("%d", vtr[i]); 
    }
    
    return 0;
}
