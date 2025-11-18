#include <math.h>

float cauchy(float x)   {
    float y = 1 / (M_PI * (1 + (x * x)));
    return y;
}

float gumbel(float x, float mu, float beta)   {
    float z = (x - mu) / beta;
    float y = (1 * exp((-1) * (z + exp((-1) * z))) / beta);
    return y;
}

float laplace(float x, float mu, float b)   {
    float z = ((-1) * fabs(x - mu)) / b;
    float y = (1 * exp(z) / (2 * b));
    return y;
}