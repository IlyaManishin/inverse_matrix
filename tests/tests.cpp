#include <gtest/gtest.h>

#include "../src/matrix_lib/utils.h"

TEST(Utils_test, transpose)
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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}