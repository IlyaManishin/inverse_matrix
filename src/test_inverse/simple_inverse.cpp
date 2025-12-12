// #include "../matrix_lib/utils/utils.h"
#include "blas_inverse.hpp"

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <cblas.h>
#include <cmath>

typedef float *mat_t;
typedef const float *const_mat_t;

static void mat_mul(const_mat_t A, const_mat_t B, mat_t C, size_t n)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
        {
            float sum = 0;
            for (size_t k = 0; k < n; k++)
                sum += A[i * n + k] * B[k * n + j];
            C[i * n + j] = sum;
        }
}

static void mat_add(mat_t A, const_mat_t B, size_t n)
{
    for (size_t i = 0; i < n * n; i++)
        A[i] += B[i];
}

static void mat_transpose(const_mat_t A, mat_t out, size_t n)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            out[j * n + i] = A[i * n + j];
}

static mat_t mat_zero(size_t n)
{
    mat_t M = (mat_t)calloc(n * n, sizeof(float));
    return M;
}

static mat_t mat_identity(size_t n)
{
    mat_t M = mat_zero(n);
    for (size_t i = 0; i < n; i++)
        M[i * n + i] = 1.0f;
    return M;
}

static mat_t get_b_matrix(const_mat_t A, size_t n)
{
    mat_t B = mat_zero(n);
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            B[j * n + i] = A[i * n + j];

    float norm = 0;
    for (size_t i = 0; i < n; i++)
    {
        float row_sum = 0;
        for (size_t j = 0; j < n; j++)
            row_sum += fabs(A[i * n + j]);
        if (row_sum > norm)
            norm = row_sum;
    }

    float scale = 1.0f / (norm * norm);

    for (size_t i = 0; i < n * n; i++)
        B[i] *= scale;

    return B;
}

static mat_t get_r_matrix(const_mat_t B, const_mat_t A, size_t n)
{
    mat_t R = mat_zero(n);
    for (size_t i = 0; i < n; i++)
        R[i * n + i] = 1.0f;

    mat_t BA = mat_zero(n);
    mat_mul(B, A, BA, n);
    for (size_t i = 0; i < n * n; i++)
        R[i] -= BA[i];

    free(BA);
    return R;
}

mat_t simple_inverse(const_mat_t A, size_t n, size_t accur)
{
    mat_t B = get_b_matrix((float *)A, n);
    mat_t R = get_r_matrix(B, A, n);

    mat_t S = mat_identity(n);
    mat_t term = mat_identity(n);
    mat_t tmp = mat_zero(n);

    for (size_t k = 1; k <= accur; k++)
    {
        mat_mul(term, R, tmp, n);

        mat_t swap = term;
        term = tmp;
        tmp = swap;

        mat_add(S, term, n);
    }

    mat_t inv = mat_zero(n);
    mat_mul(S, B, inv, n);

    free(B);
    free(R);
    free(S);
    free(term);
    free(tmp);

    return inv;
}
