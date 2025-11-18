#include <stdio.h>

int main() {
    FILE* arquivo = fopen("case.txt", "r");
    int a = 0, b = 0, c = 0, d = 0, resto = 0;
    fscanf(arquivo, "%d %d %d %d", &a, &b, &c, &d);
    while(d) {
        if(b) {
            resto = a % b;
            a = b;
            b = resto;      
        }
        else if(c) {
            resto = a % c;
            a = c;
            c = resto;
        }
        else if(d) {
            resto = a % d;
            a = d;
            d = resto;
        }
    }
    printf("%d", a);
    return 0;
}

/*
#include <stdio.h>
#include <string.h>

int main() {
    FILE* arquivo = fopen("case.txt", "r");
    int i = 0, resto = 0;
    int num[4];
    memset(num, 0, sizeof(num));
    while(!feof(arquivo)) {
        fscanf(arquivo, "%d", &num[i]);
        i++;
    }
    i = 0;
    while(num[3] != 0) {
        if(num[1]) {
            resto = num[0] % num[1];
            num[0] =num[1];
            num[1] = resto;
            
        }
    }
    return 0;
}
*/