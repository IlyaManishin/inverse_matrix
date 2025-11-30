#include "utils.h"

#include <xmmintrin.h>

void multypl_row_with_sc(float *row, size_t size, float scalar)
{
    __m128 multipl = _mm_set1_ps(scalar);
    int i = 0;
    for (; i + 3 < size; i += 4)
    {
        __m128 v = _mm_loadu_ps(row + i);
        v = _mm_mul_ps(v, multipl);
        _mm_storeu_ps(row + i, v);
    }
    for (; i < size; i++)
    {
        row[i] *= scalar;
    }
}

void div_row_with_sc(float *row, size_t size, float scalar)
{
    __m128 divider = _mm_set1_ps(scalar);
    int i = 0;
    for (; i + 3 < size; i += 4)
    {
        __m128 v = _mm_loadu_ps(row + i);
        v = _mm_div_ps(v, divider);
        _mm_storeu_ps(row + i, v);
    }
    for (; i < size; i++)
    {
        row[i] /= scalar;
    }
}

float sum_row(const float *row, size_t size)
{
    __m128 sum_vec = _mm_setzero_ps();
    size_t i = 0;

    for (; i + 3 < size; i += 4)
    {
        __m128 v = _mm_loadu_ps(row + i);
        sum_vec = _mm_add_ps(sum_vec, v);
    }

    float temp[4];
    _mm_storeu_ps(temp, sum_vec);
    float sum = temp[0] + temp[1] + temp[2] + temp[3];

    for (; i < size; ++i)
    {
        sum += row[i];
    }

    return sum;
}
