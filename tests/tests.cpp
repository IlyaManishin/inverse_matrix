#include <cblas.h>
#include <gtest/gtest.h>

#include "../src/matrix_lib/matrix_lib.h"
#include "../src/matrix_lib/utils/utils.h"

static const float TOL = 1e-1f;

TEST(UtilsTest, GetBMatrixFullCheck)
{
    size_t size = 3;

    float *matrix = get_zero_matrix(size);

    matrix[0 * size + 0] = 1;
    matrix[0 * size + 1] = 2;
    matrix[0 * size + 2] = 3;
    matrix[1 * size + 0] = 4;
    matrix[1 * size + 1] = 5;
    matrix[1 * size + 2] = 6;
    matrix[2 * size + 0] = 7;
    matrix[2 * size + 1] = 8;
    matrix[2 * size + 2] = 9;

    float *tmatrix = transpose_matrix(matrix, size);
    float *b = get_b_matrix(matrix, tmatrix, size);

    float maxRow = sum_row(&matrix[0], size);
    for (size_t i = 1; i < size; i++)
        maxRow = std::max(sum_row(&matrix[i * size], size), maxRow);

    float maxCol = sum_row(&tmatrix[0], size);
    for (size_t i = 1; i < size; i++)
        maxCol = std::max(sum_row(&tmatrix[i * size], size), maxCol);

    float divider = maxRow * maxCol;

    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
        {
            float expected = tmatrix[i * size + j] / divider;
            EXPECT_FLOAT_EQ(b[i * size + j], expected);
        }

    free(matrix);
    free(tmatrix);
    free(b);
}


TEST(MatrixInverseTest, SeriesInverseAccuracy)
{
    const size_t N = 50;
    const size_t accur = 10000;

    float *A = get_random_matrix(N, -1000.0f, 1000.0f);
    float *Ainv = get_inverse_matrix(A, N, accur);
    ASSERT_NE(Ainv, nullptr);
    float *prod = get_identity_matrix(N);
    float *tAinv = transpose_matrix(Ainv, N);
    mul_matrix(A, tAinv, prod, N);

    float *I = get_identity_matrix(N);

    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            EXPECT_NEAR(
                prod[i * N + j],
                I[i * N + j],
                0.5f);

    free_matrix(A);
    free_matrix(Ainv);
    free_matrix(prod);
    free_matrix(I);
}

TEST(MatrixMulTest, CompareWithBLAS)
{
    srand(0);
    size_t N = 1000;
    mat_t A = get_random_matrix(N, -10, 10);
    mat_t B = get_random_matrix(N, -10, 10);

    mat_t tB = transpose_matrix(B, N);
    mat_t C1 = get_zero_matrix(N);
    mul_matrix(A, tB, C1, N);

    float *C2 = (float *)malloc(N * N * sizeof(float));

    cblas_sgemm(
        CblasRowMajor,
        CblasNoTrans,
        CblasNoTrans,
        N, N, N,
        1.0f,
        A, N,
        B, N,
        0.0f,
        C2, N);

    for (int i = 0; i < N * N; i++)
    {
        EXPECT_NEAR(C1[i], C2[i], TOL);
    }

    free_matrix(A);
    free_matrix(B);
    free_matrix(tB);
    free_matrix(C1);
    free(C2);
}

TEST(UtilsTest, MultiplyRowWithScalar)
{
    float row[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float expected[] = {2.0f, 4.0f, 6.0f, 8.0f, 10.0f};
    size_t size = sizeof(row) / sizeof(row[0]);
    float scalar = 2.0f;

    multypl_row_with_sc(row, size, scalar);

    for (size_t i = 0; i < size; i++)
    {
        EXPECT_FLOAT_EQ(row[i], expected[i]);
    }
}

TEST(UtilsTest, Transpose)
{
    size_t n = 3;
    float *a = (float *)malloc(n * n * sizeof(float));

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            a[i * n + j] = i * n + j;

    float *t = transpose_matrix(a, n);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            EXPECT_FLOAT_EQ(t[i * n + j], a[j * n + i]);

    free(a);
    free(t);
}

TEST(RowsOps, AddRows)
{
    float a[4] = {1, 2, 3, 4};
    float b[4] = {5, 6, 7, 8};
    add_rows(a, b, 4);
    EXPECT_FLOAT_EQ(a[0], 6);
    EXPECT_FLOAT_EQ(a[1], 8);
    EXPECT_FLOAT_EQ(a[2], 10);
    EXPECT_FLOAT_EQ(a[3], 12);
}

TEST(RowsOps, SubRows)
{
    float a[4] = {5, 7, 9, 11};
    float b[4] = {1, 2, 3, 4};
    sub_rows(a, b, 4);
    EXPECT_FLOAT_EQ(a[0], 4);
    EXPECT_FLOAT_EQ(a[1], 5);
    EXPECT_FLOAT_EQ(a[2], 6);
    EXPECT_FLOAT_EQ(a[3], 7);
}

TEST(RowsOps, MulRows)
{
    float a[4] = {1, 2, 3, 4};
    float b[4] = {2, 3, 4, 5};
    mul_rows(a, b, 4);
    EXPECT_FLOAT_EQ(a[0], 2);
    EXPECT_FLOAT_EQ(a[1], 6);
    EXPECT_FLOAT_EQ(a[2], 12);
    EXPECT_FLOAT_EQ(a[3], 20);
}

TEST(RowsOps, DivRows)
{
    float a[4] = {10, 20, 30, 40};
    float b[4] = {2, 4, 5, 8};
    div_rows(a, b, 4);
    EXPECT_FLOAT_EQ(a[0], 5);
    EXPECT_FLOAT_EQ(a[1], 5);
    EXPECT_FLOAT_EQ(a[2], 6);
    EXPECT_FLOAT_EQ(a[3], 5);
}

TEST(SumRowTest, BasicCases)
{
    float row1[] = {1.0f, 2.0f, 3.0f, 4.0f};
    float row2[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float row3[] = {0.0f, 0.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(sum_row(row1, 4), 10.0f);
    EXPECT_FLOAT_EQ(sum_row(row2, 5), 15.0f);
    EXPECT_FLOAT_EQ(sum_row(row3, 4), 0.0f);
}

TEST(SumRowTest, SingleElement)
{
    float row[] = {42.0f};
    EXPECT_FLOAT_EQ(sum_row(row, 1), 42.0f);
}

TEST(MatrixMulTest, Identity)
{
    const size_t n = 3;

    float *a = get_zero_matrix(n);
    float *ident = get_identity_matrix(n);

    a[0 * n + 0] = 2;
    a[0 * n + 1] = 3;
    a[0 * n + 2] = 4;
    a[1 * n + 0] = 5;
    a[1 * n + 1] = 6;
    a[1 * n + 2] = 7;
    a[2 * n + 0] = 8;
    a[2 * n + 1] = 9;
    a[2 * n + 2] = 10;

    float *it = transpose_matrix(ident, n);
    float *c = get_zero_matrix(n);
    mul_matrix(a, it, c, n);

    for (size_t y = 0; y < n; y++)
        for (size_t x = 0; x < n; x++)
            EXPECT_FLOAT_EQ(c[y * n + x], a[y * n + x]);

    free(a);
    free(ident);
    free(it);
    free(c);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}