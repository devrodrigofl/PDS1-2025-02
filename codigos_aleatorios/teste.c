#include <stdio.h>

int main() {
    
    float a = 0, b = 0, c = 0;

    if(a <= 0) {
        a += 1;
        b = 3;
    } 
    else {
        b = 5;
    }

    printf("%.1f\n", b);

    return 0;
}