#pragma once
#include "types.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    mat_t copy_matrix(const_mat_t src, size_t size);
    mat_t transpose_matrix(const_mat_t src, size_t size);
    mat_t transpose_cur_mat(mat_t matrix, size_t size);
    void div_matrix_with_sc(mat_t matrix, size_t size, float scalar);
    mat_t get_b_matrix(const_mat_t matrix, const_mat_t tmatrix, size_t size);
    void sub_matrix(mat_t dest, mat_t src, size_t size);
    void add_matrix(mat_t dest, mat_t src, size_t size);
    mat_t mul_matrix(const_mat_t left, const_mat_t tright, mat_t dest, size_t size);

    void multypl_row_with_sc(float *row, size_t size, float scalar);
    void div_row_with_sc(float *row, size_t size, float scalar);

    void add_rows(float *row1, const float *row2, size_t size);
    void sub_rows(float *row1, const float *row2, size_t size);
    void mul_rows(float *row1, const float *row2, size_t size);
    void div_rows(float *row1, const float *row2, size_t size);
    float sum_row(const float *row, size_t size);
    float abs_sum_row(const float *row, size_t size);
    
    void mul_rows_buf(const float *row1, const float *row2, float *buf, size_t size);
    float scalar_mul_row_aligned(const float *row1, const float *row2, size_t size);
    float scalar_mul_row(const float *row1, const float *row2, size_t size);
#ifdef __cplusplus
}
#endif
