#include <stdio.h>
#include <string.h>

int main()  {

    int n = 0, i = 0;
    scanf("%d", &n);
    int vtr[n];
    memset(vtr, 0, n * 4);

    for(i = 0; i < n; i++) {
        scanf("%d", &vtr[i]); 
    }
    
    for(i = i - 1; i >= 0; i--) {
        printf("%d\n", vtr[i]);
    }

    return 0;
}