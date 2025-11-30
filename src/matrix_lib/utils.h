#pragma once
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    float **zero_matrix(size_t size);
    float **identity_matrix(size_t size);
    float **copy_matrix(float **src, size_t size);
    float **transpose_matrix(float **src, size_t size);
    void div_matrix_with_sc(float **matrix, size_t size, float scalar);
    float **get_b_matrix(float **matrix, float **tmatrix, size_t size);

    void multypl_row_with_sc(float *row, size_t size, float scalar);
    void div_row_with_sc(float *row, size_t size, float scalar);
    float sum_row(const float *row, size_t size);

#ifdef __cplusplus
}
#endif