#include "../matrix_lib.h"
#include "types.h"
#include "utils.h"

#define max(a, b) (a) > (b) ? (a) : (b)

matrix_t transpose_matrix(const_matrix_t src, size_t size)
{
    matrix_t res = (matrix_t)malloc(size * sizeof(row_t));
    for (size_t i = 0; i < size; i++)
    {
        res[i] = (row_t)malloc(size * sizeof(float));
        for (int j = 0; j < size; j++)
        {
            res[i][j] = src[j][i];
        }
    }
    return res;
}

matrix_t copy_matrix(const_matrix_t src, size_t size)
{
    matrix_t res = (matrix_t)malloc(size * sizeof(row_t));
    for (size_t i = 0; i < size; i++)
    {
        res[i] = (row_t)malloc(size * sizeof(float));
        for (size_t j = 0; j < size; j++)
        {
            res[i][j] = src[i][j];
        }
    }
    return res;
}

void div_matrix_with_sc(matrix_t matrix, size_t size, float scalar)
{
    for (size_t i = 0; i < size; i++)
        div_row_with_sc(matrix[i], size, scalar);
}

matrix_t mul_matrix(const_matrix_t left, const_matrix_t tright, float *buf, size_t size)
{
    matrix_t res = get_zero_matrix(size);
    for (size_t y = 0; y < size; y++)
    {
        for (size_t x = 0; x < size; x++)
        {
            mul_rows_buf(left[y], tright[x], buf, size);
            res[y][x] = sum_row(buf, size);
        }
    }
    return res;
}

matrix_t get_b_matrix(const_matrix_t matrix, const_matrix_t tmatrix, size_t size)
{
    float maxRow, maxCol;
    maxRow = sum_row(matrix[0], size);
    maxCol = sum_row(tmatrix[0], size);

    for (size_t i = 1; i < size; i++)
    {
        maxRow = max(sum_row(matrix[i], size), maxRow);
        maxCol = max(sum_row(tmatrix[i], size), maxCol);
    }
    float divider = maxRow * maxCol;
    matrix_t b_matrix = copy_matrix(tmatrix, size);
    div_matrix_with_sc(b_matrix, size, divider);

    return b_matrix;
}

matrix_t get_zero_matrix_internal(size_t size)
{
    matrix_t mat = (matrix_t)malloc(size * sizeof(row_t));
    for (size_t i = 0; i < size; i++)
    {
        mat[i] = (row_t)calloc(size, sizeof(float));
    }
    return mat;
}

matrix_t get_identity_matrix_internal(size_t size)
{
    matrix_t mat = get_zero_matrix(size);
    for (size_t i = 0; i < size; i++)
    {
        mat[i][i] = 1.0f;
    }
    return mat;
}
