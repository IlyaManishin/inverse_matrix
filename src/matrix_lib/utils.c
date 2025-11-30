#include "utils.h"

float **transpose_matrix(float **src, size_t size)
{
    float **res = (float **)malloc(size * sizeof(float *));
    for (size_t i = 0; i < size; i++)
    {
        res[i] = (float *)malloc(size * sizeof(float));
        for (int j = 0; j < size; j++)
        {
            res[i][j] = src[j][i];
        }
    }
    return res;
}
