
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Maxfiles.h"
#include <MaxSLiCInterface.h>

#define valueType float
#define indexType uint32_t

#define MAX_ITER 1

const long long dataSize = 1024 * 1024 * 1024;

int main() 
{
    printf("Multi-pumping study: Origin Loop version\n");
    printf("dataSize = %d\n", dataSize);
    const size_t inputBytes = sizeof(valueType) * dataSize;
    const size_t outputBytes = sizeof(valueType) * dataSize;
    valueType *x = malloc(inputBytes);
    valueType *y = malloc(inputBytes);
    valueType *z0 = malloc(outputBytes);
    valueType *z1 = malloc(outputBytes);
    
    for (int i = 0; i < dataSize; i++) {
        x[i] = i * 2;
        y[i] = i * 2 + 1;
    }

    printf("Running DFE...\n");
    struct timeval t0, t1;
    gettimeofday(&t0, 0);
    for (int i = 0; i < MAX_ITER; i++) {
        OriginLoop(dataSize, x, y, z0, z1);
    }
    gettimeofday(&t1, 0);

    double duration = (double)(t1.tv_sec-t0.tv_sec)+(double)(t1.tv_usec-t0.tv_usec)/1e6;

    duration /= MAX_ITER;
    printf("total time taken by DFE: %lf s\n", duration);
    printf("per element time taken by DFE: %lf ns %lf MHz\n", 
        duration * 1e9 / (2 * dataSize),
        1 / (duration / (2 * dataSize)) / 1e6);
    for (int i = 0; i < 10; i++) {
        printf("z0[%3d] = %f\n", i, z0[i]);
        printf("z1[%3d] = %f\n", i, z1[i]);
    }

    return 0;
} 