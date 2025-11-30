#include "matrix_lib.h"
#include "utils.h"

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

    return nullptr;
}
