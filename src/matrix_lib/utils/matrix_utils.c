#include "utils.h"

#define max(a, b) (a) > (b) ? (a) : (b)

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

float **copy_matrix(float **src, size_t size)
{
    float **res = (float **)malloc(size * sizeof(float *));
    for (size_t i = 0; i < size; i++)
    {
        res[i] = (float *)malloc(size * sizeof(float));
        for (size_t j = 0; j < size; j++)
        {
            res[i][j] = src[i][j];
        }
    }
    return res;
}

void div_matrix_with_sc(float **matrix, size_t size, float scalar)
{
    for (size_t i = 0; i < size; i++)
        div_row_with_sc(matrix[i], size, scalar);
}

float **get_b_matrix(float **matrix, float **tmatrix, size_t size)
{
    float maxRow, maxCol;
    maxRow = sum_row(matrix[0], size);
    maxCol = sum_row(tmatrix[0], size);

    for (size_t i = 1; i < size; i++) // or split?
    {
        maxRow = max(sum_row(matrix[i], size), maxRow);
        maxCol = max(sum_row(tmatrix[i], size), maxCol);
    }
    float divider = maxRow * maxCol;
    float **b_matrix = copy_matrix(tmatrix, size);
    div_matrix_with_sc(b_matrix, size, divider);

    return b_matrix;
}
