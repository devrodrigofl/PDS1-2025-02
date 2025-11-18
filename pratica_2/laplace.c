#include <math.h>

float laplace(float x, float mu, float b)   {
    float z = ((-1) * fabs(x - mu)) / b;
    float y = (1 * exp(z) / (2 * b));
    return y;
}