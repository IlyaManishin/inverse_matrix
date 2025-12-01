#pragma once
#include "types.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    matrix_t copy_matrix(const_matrix_t src, size_t size);
    matrix_t transpose_matrix(const_matrix_t src, size_t size);
    void div_matrix_with_sc(matrix_t matrix, size_t size, float scalar);
    matrix_t get_b_matrix(const_matrix_t matrix, const_matrix_t tmatrix, size_t size);
    matrix_t mul_matrix(const_matrix_t left, const_matrix_t tright, float *buf, size_t size);

    matrix_t get_zero_matrix_internal(size_t size);
    matrix_t get_identity_matrix_internal(size_t size);
    row_t get_row(size_t size);
    void free_row(row_t row);

    void multypl_row_with_sc(float *row, size_t size, float scalar);
    void div_row_with_sc(float *row, size_t size, float scalar);

    void add_rows(float *row1, const float *row2, size_t size);
    void sub_rows(float *row1, const float *row2, size_t size);
    void mul_rows(float *row1, const float *row2, size_t size);
    void div_rows(float *row1, const float *row2, size_t size);
    float sum_row(const float *row, size_t size);

    void mul_rows_buf(const float *row1, const float *row2, float *buf, size_t size);

#ifdef __cplusplus
}
#endif
