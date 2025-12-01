#include "matrix_lib.h"
#include "utils/types.h"
#include "utils/utils.h"

mat_t get_zero_matrix(size_t size)
{
    mat_t mat = (mat_t)calloc(size * size, sizeof(float));
    return mat;
}

mat_t get_identity_matrix(size_t size)
{
    mat_t mat = get_zero_matrix(size);
    for (size_t i = 0; i < size; i++)
        mat[i * size + i] = 1.0f;
    return mat;
}

mat_t get_random_matrix(size_t size, float min_val, float max_val)
{
    mat_t mat = (mat_t)malloc(size * size * sizeof(float));
    for (size_t i = 0; i < size * size; i++)
    {
        float r = (float)rand() / (float)RAND_MAX; 
        mat[i] = min_val + r * (max_val - min_val);
    }
    return mat;
}


void free_matrix(mat_t matrix)
{
    free(matrix);
}

float **get_inverse_matrix(mat_t matrix, size_t size)
{
    if (size == 0)
        return NULL;

    mat_t tmatrix = transpose_matrix(matrix, size);
    mat_t bmatrix = get_b_matrix(matrix, (const_mat_t)tmatrix, size);
    return NULL;
}
