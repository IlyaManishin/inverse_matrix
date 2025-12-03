#include "../matrix_lib.h"
#include "types.h"
#include "utils.h"

#include <string.h>

#define max(a, b) (a) > (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)

#define L1_CASH_SIZE 4 * 1024
#define BLOCK_SIZE_FLOATS 128

mat_t transpose_matrix(const_mat_t src, size_t size)
{
    mat_t res = (mat_t)malloc(size * size * sizeof(float));
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            res[i * size + j] = src[j * size + i];
    return res;
}

mat_t transpose_cur_mat(mat_t matrix, size_t size)
{
    float tmp;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size; j++)
        {
            tmp = matrix[i * size + j];
            matrix[i * size + j] = matrix[j * size + i];
            matrix[j * size + i] = tmp;
        }
    }
    return matrix;
}

mat_t copy_matrix(const_mat_t src, size_t size)
{
    mat_t res = (mat_t)malloc(size * size * sizeof(float));
    memcpy(res, src, size * size * sizeof(float));
    return res;
}

void div_matrix_with_sc(mat_t matrix, size_t size, float scalar)
{
    for (size_t i = 0; i < size * size; i++)
        matrix[i] /= scalar;
}

void sub_matrix(mat_t dest, mat_t src, size_t size)
{
    sub_rows(dest, src, size);
}

void add_matrix(mat_t dest, mat_t src, size_t size)
{
    add_rows(dest, src, size);
}

static inline void mul_block_16(
    const_mat_t A_block,
    const_mat_t B_block,
    float *C_block,
    size_t n,
    size_t k_start)
{
    for (size_t y = 0; y < BLOCK_SIZE_FLOATS; y++)
    {
        const float *rowA = A_block + y * n + k_start;
        float *rowC = C_block + y * n;

        for (size_t x = 0; x < BLOCK_SIZE_FLOATS; x++)
        {
            const float *rowB = B_block + x * n + k_start;
            float add = scalar_mul_row_aligned(rowA, rowB, BLOCK_SIZE_FLOATS);
            rowC[x] += add;
        }
    }
}

mat_t mul_matrix(const_mat_t left, const_mat_t tright, mat_t dest, size_t size)
{
    for (size_t i = 0; i < size * size; i++)
        dest[i] = 0;

    size_t full_blocks = size / BLOCK_SIZE_FLOATS;
    size_t tail = size % BLOCK_SIZE_FLOATS;

    for (size_t by = 0; by < full_blocks; by++)
    {
        for (size_t bx = 0; bx < full_blocks; bx++)
        {
            size_t byOff = by * BLOCK_SIZE_FLOATS;
            size_t bxOff = bx * BLOCK_SIZE_FLOATS;

            const float *A_block = left + byOff * size;
            const float *B_block = tright + bxOff * size;
            float *C_block = dest + byOff * size + bxOff;

            for (size_t bk = 0; bk < full_blocks; bk++)
            {
                size_t kStart = bk * BLOCK_SIZE_FLOATS;
                mul_block_16(A_block, B_block, C_block, size, kStart);
            }

            if (tail)
            {
                size_t kStart = full_blocks * BLOCK_SIZE_FLOATS;
                for (size_t y = 0; y < BLOCK_SIZE_FLOATS; y++)
                {
                    const float *rowA = A_block + y * size + kStart;
                    float *rowC = C_block + y * size;
                    for (size_t x = 0; x < BLOCK_SIZE_FLOATS; x++)
                    {
                        const float *rowB = B_block + x * size + kStart;
                        rowC[x] += scalar_mul_row(rowA, rowB, tail);
                    }
                }
            }
        }
    }

    size_t full = full_blocks * BLOCK_SIZE_FLOATS;
    for (size_t by = 0; by < full_blocks; by++)
    {
        size_t byOff = by * BLOCK_SIZE_FLOATS;
        for (size_t y = 0; y < BLOCK_SIZE_FLOATS; y++)
        {
            const float *rowA = left + (byOff + y) * size;
            for (size_t x = full; x < size; x++)
            {
                const float *rowB = tright + x * size;
                dest[(byOff + y) * size + x] += scalar_mul_row(rowA, rowB, size);
            }
        }
    }

    for (size_t y = full; y < size; y++)
    {
        const float *rowA = left + y * size;
        for (size_t x = 0; x < size; x++)
        {
            const float *rowB = tright + x * size;
            dest[y * size + x] += scalar_mul_row(rowA, rowB, size);
        }
    }

    return dest;
}

mat_t get_b_matrix(const_mat_t matrix, const_mat_t tmatrix, size_t size)
{
    float maxRow = sum_row(matrix, size);
    float maxCol = sum_row(tmatrix, size);

    for (size_t i = 1; i < size; i++)
    {
        float rowSum = sum_row(matrix + size * i, size);
        float colSum = sum_row(tmatrix + size * i, size);

        maxRow = max(rowSum, maxRow);
        maxCol = max(colSum, maxCol);
    }

    float divider = maxRow * maxCol;
    mat_t b_matrix = copy_matrix(tmatrix, size);
    div_matrix_with_sc(b_matrix, size, divider);

    return b_matrix;
}
