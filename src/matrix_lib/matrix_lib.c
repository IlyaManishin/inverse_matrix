#include "matrix_lib.h"
#include "utils/types.h"
#include "utils/utils.h"

float **get_zero_matrix(size_t size)
{
    return (float **)get_zero_matrix_internal(size);
}

float **get_identity_matrix(size_t size)
{
    return (float **)get_identity_matrix_internal(size);
}

void free_matrix(float **matrix, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

float **get_inverse_matrix(const float **matrix, size_t size)
{
    if (size == 0)
        return NULL;
    row_t buf = get_row(size);

    matrix_t tmatrix = transpose_matrix(matrix, size);
    matrix_t bmatrix = get_b_matrix(matrix, (const_matrix_t)tmatrix, size);
    return NULL;
}
