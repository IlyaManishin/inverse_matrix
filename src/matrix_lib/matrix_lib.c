#include "matrix_lib.h"
#include "utils/utils.h"

float **zero_matrix(size_t size)
{
    float **mat = (float **)malloc(size * sizeof(float *));
    for (size_t i = 0; i < size; i++)
    {
        mat[i] = (float *)calloc(size, sizeof(float));
    }
    return mat;
}

float **identity_matrix(size_t size)
{
    float **mat = zero_matrix(size);
    for (size_t i = 0; i < size; i++)
    {
        mat[i][i] = 1.0f;
    }
    return mat;
}

void free_matrix(float **matrix, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

float **inverse_matrix(float **matrix, size_t size)
{
    if (size == 0)
        return NULL;

    float **tmatrix = transpose_matrix(matrix, size);
    float **bmatrix = get_b_matrix(matrix, tmatrix, size);
    return NULL;
}
