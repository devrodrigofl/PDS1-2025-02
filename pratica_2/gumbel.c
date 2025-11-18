#include <math.h>

float gumbel(float x, float mu, float beta)   {
    float z = (x - mu) / beta;
    float y = (1 * exp((-1) * (z + exp((-1) * z))) / beta);
    return y;
}
