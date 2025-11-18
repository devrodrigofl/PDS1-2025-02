#include <stdio.h>
#include <string.h>

int main()  {

    int n1 = 0, n2 = 0, n3 = 0, menor = 0;

    scanf("%d", &n1);
    int pds[n1];
    memset(pds, 0, n1 * 4);
    for(int i = 0; i < n1; i++) {
        scanf("%d", &pds[i]); 
    }

    scanf("%d", &n2);
    int cal[n2];
    memset(cal, 0, n2 * 4);
    for(int i = 0; i < n2; i++) {
        scanf("%d", &cal[i]); 
    }

    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < n2; j++) {
            if(pds[i] == cal[j]) {
                printf("%d\n", pds[i]);
            }
        }
    }

    return 0;
}