#include <stdio.h>

int main()  {

    float a = 0, b = 0, c = 0;
    scanf("%f %f %f", &a, &b, &c);

    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Valores invalidos\n");
    } else if ((a > b + c) || (b > a + c) || (c > b + a)) {
        printf("Triangulo invalido\n");
    } else {
        if (a == b && a == c) {
            printf("Triangulo equilatero\n");
        } else if ((a != b && (a == c ^ b == c)) || (b != c && (b == a ^ c == a))) {
            printf("Triangulo isosceles\n");
        } else if (a != b && a!= c) {
            printf("Triangulo escaleno\n");
        }
    }

    return 0;
}