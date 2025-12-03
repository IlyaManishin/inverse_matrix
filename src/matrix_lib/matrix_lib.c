#include "matrix_lib.h"
#include "utils/types.h"
#include "utils/utils.h"

#include <stdio.h>

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

void print_matrix(float *mat, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            printf("%f ", mat[size * i + j]);
        }
        printf("\n");
    }
}

static inline void add_ident(mat_t dest, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        dest[size * i + i] += 1;
    }
}

static inline mat_t get_rmatrix(const_mat_t bmatrix, const_mat_t tmatrix, size_t size)
{
    mat_t rmatrix = get_zero_matrix(size);
    mul_matrix(bmatrix, tmatrix, rmatrix, size);
    mul_matrix_to_sc(rmatrix, size, -1);
    add_ident(rmatrix, size);

    return rmatrix;
}

// static mat_t get_series(mat_t rmatrix, mat_t buf, size_t size, size_t accur)
// {
//     mat_t accum = get_identity_matrix(size);
//     print_matrix(rmatrix, size);
//     add_matrix(accum, rmatrix, size);
//     transpose_cur_mat(rmatrix, size);

//     for (size_t i = 0; i <= accur; i++)
//     {
//         mul_matrix(accum, rmatrix, buf, size);

//         mat_t temp = buf;
//         buf = accum;
//         accum = temp;
//         add_ident(accum, size);
//         print_matrix(accum, size);
//     }
//     return accum;
// }

static mat_t get_series(mat_t rmatrix, mat_t buf, size_t size, size_t accur)
{
    mat_t S = get_identity_matrix(size);
    mat_t term = copy_matrix(rmatrix, size);

    for (size_t k = 1; k <= accur; k++)
    {
        print_matrix(S, size);
        add_matrix(S, term, size);

        mat_t next_term = get_zero_matrix(size);
        mul_matrix(term, rmatrix, next_term, size);
        free_matrix(term);
        term = next_term;
    }

    free_matrix(term);
    return S;
}

float *get_inverse_matrix(mat_t matrix, size_t size, size_t accur)
{
    if (size == 0)
        return NULL;
    mat_t buf = get_zero_matrix(size);

    mat_t tmatrix = transpose_matrix(matrix, size);
    mat_t bmatrix = get_b_matrix(matrix, tmatrix, size);
    mat_t rmatrix = get_rmatrix(bmatrix, tmatrix, size);

    mat_t series = get_series(rmatrix, buf, size, accur);
    mat_t tbmatrix = transpose_cur_mat(bmatrix, size);
    mul_matrix(series, tbmatrix, buf, size);

    free_matrix(tmatrix);
    free_matrix(tbmatrix);

    return buf;
}
