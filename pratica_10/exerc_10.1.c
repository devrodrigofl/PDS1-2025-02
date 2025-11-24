#include <stdio.h>
#include <stdlib.h>

float* read_array(int* n) {
    scanf("%d", n);
    float* array = NULL;
    array = (float*) malloc(*n * sizeof(float));
    for(int i = 0; i < *n; i++) {
        scanf("%f", &array[i]);
    }
    return array; 
}

void* free_array(float* array) {
    free(array);
}