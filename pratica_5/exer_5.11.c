#include <stdio.h>

float raiz1(float x) {
    float y = 1;
    while ((y * y) - x < 0.01 || (y * y) - x > 0.01) {
        printf("%f\n", y);
        if ((y * y) - x < 0.01) y *= 1.2;
        else if ((y * y) - x > 0.01) y *= 0.9;
        printf("%f\n", y);
    } return y;
    return y;
}

float raiz(float x) {
    float low = 0.0;
    float high = x;
    float y = x / 2.0;

    while ((y * y - x) >= 0.01 || (y * y - x) <= -0.01) {
        
        if (y * y > x) {
            high = y;
        }
        else {
            low = y;
        }
        y = (low + high) / 2.0;
    }

    return y;
}

int main()  {

    printf("%f\n", raiz(100));

    return 0;
}
