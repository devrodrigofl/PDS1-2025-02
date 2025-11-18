#include <stdio.h>

int tipoChar (char x)   {
    if (x >= '0' && x <= '9') {
        return 0;
    } else if (x >= 'A' && x <= 'Z')  {
        return 1;
    } else if (x >= 'a' && x <= 'z') {
        return 2;
    } else return -1;
}

int contemApenasUmNumero (char x, char y, char z)   {
    int count = 0;
    count = !tipoChar(x) + !tipoChar(y) + !tipoChar(z);
    return count == 1;
}

void colocaMaiuscula (char *a) {
    if (*a >= 'a' && *a <= 'z') {
        *a = *a & ~32;
    }
}

int verifica(char a, char b, char c)    {
    int count = 0;
    if(tipoChar(a) != -1) count++;
    if(tipoChar(b) != -1) count++;
    if(tipoChar(b) != -1) count++;
    return count == 3;
}

float calcularArea(float x1, float y1, float x2, float y2)   {
    float area = (x2 - x1) * (y2 - y1);
    if(area < 0) {
        return (area * -1);
    } else return area;
}



int main()  {

    char a, b, c;
    scanf("%c %c %c", &a, &b, &c);

    if (!contemApenasUmNumero(a, b, c) || !verifica(a, b, c)) {
    printf("\nErro!");
    return -1;
    }

    colocaMaiuscula(&a);
    colocaMaiuscula(&b);
    colocaMaiuscula(&c);

    printf ("pin aceito: %c%c%c\n", a, b, c);

    return 0;
}

int main()  {

    float x1 = 2, y1 = 2, x2 = 0, y2 = 0;
    
    printf ("%f\n", calcularArea(x1, y1, x2, y2));

    return 0;
}