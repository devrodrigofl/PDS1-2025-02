#include <math.h>

float cauchy(float x)   {
    float y = 1 / (M_PI * (1 + (x * x)));
    return y;
}