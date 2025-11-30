#include <gtest/gtest.h>

#include "../src/matrix_lib/matrix_lib.h"
#include "../src/matrix_lib/utils.h"

TEST(UtilsTest, transpose)
{
    size_t n = 3;
    float **a = (float **)malloc(n * sizeof(float *));
    for (size_t i = 0; i < n; i++)
    {
        a[i] = (float *)malloc(n * sizeof(float));
        for (size_t j = 0; j < n; j++)
            a[i][j] = i * n + j;
    }

    float **t = transpose_matrix(a, n);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            EXPECT_FLOAT_EQ(t[i][j], a[j][i]);

    for (size_t i = 0; i < n; i++)
    {
        free(a[i]);
        free(t[i]);
    }
    free(a);
    free(t);
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

TEST(UtilsTest, GetBMatrixFullCheck)
{
    size_t size = 3;

    // Исходная матрица
    float **matrix = zero_matrix(size);

    // Задаем конкретные значения для matrix
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 3;
    matrix[1][0] = 4;
    matrix[1][1] = 5;
    matrix[1][2] = 6;
    matrix[2][0] = 7;
    matrix[2][1] = 8;
    matrix[2][2] = 9;

    float **tmatrix = transpose_matrix(matrix, size);
    // Вызываем функцию
    float **b = get_b_matrix(matrix, tmatrix, size);

    // Вычисляем ожидаемый делитель
    float maxRow = std::max(sum_row(matrix[0], size), std::max(sum_row(matrix[1], size), sum_row(matrix[2], size)));
    float maxCol = std::max(sum_row(tmatrix[0], size), std::max(sum_row(tmatrix[1], size), sum_row(tmatrix[2], size)));
    float divider = maxRow * maxCol;

    // Проверяем корректность каждого элемента b_matrix
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            float expected = tmatrix[i][j] / divider;
            EXPECT_FLOAT_EQ(b[i][j], expected);
        }
    }

    free_matrix(matrix, size);
    free_matrix(tmatrix, size);
    free_matrix(b, size);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}