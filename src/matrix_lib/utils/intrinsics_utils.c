#include "utils.h"
#include "types.h"

#include <immintrin.h>
#include <stdlib.h>
#include <stddef.h>

float *get_row(size_t size)
{
    return (float *)calloc(size, sizeof(float));
}

void free_row(row_t row)
{
    free(row);
}

void multypl_row_with_sc(float *row, size_t size, float scalar)
{
    __m256 multipl = _mm256_set1_ps(scalar);
    size_t i = 0;
    for (; i + 7 < size; i += 8)
    {
        __m256 v = _mm256_loadu_ps(row + i);
        v = _mm256_mul_ps(v, multipl);
        _mm256_storeu_ps(row + i, v);
    }
    for (; i < size; i++)
        row[i] *= scalar;
}

void div_row_with_sc(float *row, size_t size, float scalar)
{
    __m256 divider = _mm256_set1_ps(scalar);
    size_t i = 0;
    for (; i + 7 < size; i += 8)
    {
        __m256 v = _mm256_loadu_ps(row + i);
        v = _mm256_div_ps(v, divider);
        _mm256_storeu_ps(row + i, v);
    }
    for (; i < size; i++)
        row[i] /= scalar;
}

void add_rows(float *row1, const float *row2, size_t size)
{
    size_t i = 0;
    for (; i + 7 < size; i += 8)
    {
        __m256 a = _mm256_loadu_ps(row1 + i);
        __m256 b = _mm256_loadu_ps(row2 + i);
        a = _mm256_add_ps(a, b);
        _mm256_storeu_ps(row1 + i, a);
    }
    for (; i < size; i++)
        row1[i] += row2[i];
}

void sub_rows(float *row1, const float *row2, size_t size)
{
    size_t i = 0;
    for (; i + 7 < size; i += 8)
    {
        __m256 a = _mm256_loadu_ps(row1 + i);
        __m256 b = _mm256_loadu_ps(row2 + i);
        a = _mm256_sub_ps(a, b);
        _mm256_storeu_ps(row1 + i, a);
    }
    for (; i < size; i++)
        row1[i] -= row2[i];
}

void mul_rows(float *row1, const float *row2, size_t size)
{
    size_t i = 0;
    for (; i + 7 < size; i += 8)
    {
        __m256 a = _mm256_loadu_ps(row1 + i);
        __m256 b = _mm256_loadu_ps(row2 + i);
        a = _mm256_mul_ps(a, b);
        _mm256_storeu_ps(row1 + i, a);
    }
    for (; i < size; i++)
        row1[i] *= row2[i];
}

void mul_rows_buf(const float *row1, const float *row2, float *buf, size_t size)
{
    size_t i = 0;
    for (; i + 7 < size; i += 8)
    {
        __m256 a = _mm256_loadu_ps(row1 + i);
        __m256 b = _mm256_loadu_ps(row2 + i);
        a = _mm256_mul_ps(a, b);
        _mm256_storeu_ps(buf + i, a);
    }
    for (; i < size; i++)
        buf[i] = row1[i] * row2[i];
}

void div_rows(float *row1, const float *row2, size_t size)
{
    size_t i = 0;
    for (; i + 7 < size; i += 8)
    {
        __m256 a = _mm256_loadu_ps(row1 + i);
        __m256 b = _mm256_loadu_ps(row2 + i);
        a = _mm256_div_ps(a, b);
        _mm256_storeu_ps(row1 + i, a);
    }
    for (; i < size; i++)
        row1[i] /= row2[i];
}

float sum_row(const float *row, size_t size)
{
    __m256 sum_vec = _mm256_setzero_ps();
    size_t i = 0;
    for (; i + 7 < size; i += 8)
    {
        __m256 v = _mm256_loadu_ps(row + i);
        sum_vec = _mm256_add_ps(sum_vec, v);
    }

    float temp[8];
    _mm256_storeu_ps(temp, sum_vec);
    float sum = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7];

    for (; i < size; ++i)
        sum += row[i];

    return sum;
}

float scalar_mul_row(const float *row1, const float *row2, size_t size) {
    __m256 sum_vec = _mm256_setzero_ps();
    size_t i = 0;

    for (; i + 7 < size; i += 8) {
        __m256 a = _mm256_loadu_ps(row1 + i);
        __m256 b = _mm256_loadu_ps(row2 + i);
        sum_vec = _mm256_add_ps(sum_vec, _mm256_mul_ps(a, b));
    }

    float temp[8];
    _mm256_storeu_ps(temp, sum_vec);
    float sum = temp[0] + temp[1] + temp[2] + temp[3] +
                temp[4] + temp[5] + temp[6] + temp[7];

    for (; i < size; i++)
        sum += row1[i] * row2[i];

    return sum;
}
