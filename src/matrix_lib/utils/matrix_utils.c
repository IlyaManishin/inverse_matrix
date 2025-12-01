#include "../matrix_lib.h"
#include "types.h"
#include "utils.h"

#define max(a, b) (a) > (b) ? (a) : (b)

mat_t transpose_matrix(const_mat_t src, size_t size)
{
    mat_t res = (mat_t)malloc(size * size * sizeof(float));
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            res[i * size + j] = src[j * size + i];
    return res;
}

mat_t copy_matrix(const_mat_t src, size_t size)
{
    mat_t res = (mat_t)malloc(size * size * sizeof(float));
    for (size_t i = 0; i < size * size; i++)
        res[i] = src[i];
    return res;
}

void div_matrix_with_sc(mat_t matrix, size_t size, float scalar)
{
    for (size_t i = 0; i < size * size; i++)
        matrix[i] /= scalar;
}

mat_t mul_matrix(const_mat_t left, const_mat_t right, size_t size)
{
    mat_t res = get_zero_matrix(size);
    for (size_t y = 0; y < size; y++)
        for (size_t x = 0; x < size; x++)
        {
            res[size * y + x] = scalar_mul_row(left + size * y, right + size * x, size);
        }
    return res;
}

mat_t get_b_matrix(const_mat_t matrix, const_mat_t tmatrix, size_t size)
{
    float maxRow = sum_row(matrix, size);
    float maxCol = sum_row(tmatrix, size);

    for (size_t i = 1; i < size; i++)
    {
        float rowSum = sum_row(matrix + size * i, size);
        float colSum = sum_row(matrix + size * i, size);

        maxRow = max(rowSum, maxRow);
        maxCol = max(colSum, maxCol);
    }

    float divider = maxRow * maxCol;
    mat_t b_matrix = copy_matrix(tmatrix, size);
    div_matrix_with_sc(b_matrix, size, divider);

    return b_matrix;
}
