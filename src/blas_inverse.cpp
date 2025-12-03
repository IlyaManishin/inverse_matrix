#include <cblas.h>
#include <cmath>
#include <stdlib.h>

typedef float *mat_t;

static mat_t mat_zero(size_t n)
{
    mat_t m = (mat_t)calloc(n * n, sizeof(float));
    return m;
}

static mat_t mat_identity(size_t n)
{
    mat_t m = mat_zero(n);
    for (size_t i = 0; i < n; i++)
        m[i * n + i] = 1.0f;
    return m;
}

static mat_t mat_transpose(const mat_t A, size_t n)
{
    mat_t T = mat_zero(n);
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            T[j * n + i] = A[i * n + j];
    return T;
}

static void mat_mul_blas(const mat_t A, const mat_t B, mat_t C, size_t n)
{
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                n, n, n, 1.0f, A, n, B, n, 0.0f, C, n);
}

static void mat_add(const mat_t A, const mat_t B, size_t n)
{
    cblas_saxpy((int)(n * n), 1.0f, B, 1, A, 1);
}

static mat_t get_r_matrix(const mat_t B, const mat_t A, size_t n)
{
    mat_t BA = mat_zero(n);
    mat_mul_blas(B, A, BA, n);

    for (size_t i = 0; i < n; i++)
        BA[i * n + i] = 1.0f - BA[i * n + i];

    cblas_sscal((int)(n * n), -1.0f, BA, 1);

    for (size_t i = 0; i < n; i++)
        BA[i * n + i] += 1.0f;

    return BA;
}

static mat_t get_b_matrix(const mat_t A, size_t n)
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

mat_t inverse_by_series_blas(const mat_t A, size_t n, size_t accur)
{
    mat_t B = get_b_matrix(A, n);
    mat_t R = get_r_matrix(B, A, n);

    mat_t S = mat_identity(n);
    mat_t term = mat_identity(n);
    mat_t tmp = mat_zero(n);

    for (size_t k = 1; k <= accur; k++)
    {
        mat_mul_blas(term, R, tmp, n);

        mat_t swap = term;
        term = tmp;
        tmp = swap;

        mat_add(S, term, n);
    }

    mat_t inv = mat_zero(n);
    mat_mul_blas(S, B, inv, n);

    free(B);
    free(R);
    free(S);
    free(term);
    free(tmp);

    return inv;
}
