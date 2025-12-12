#include "matrix_lib/matrix_lib.h"
#include "matrix_lib/utils/utils.h"

#include "test_inverse/blas_inverse.hpp"
#include "test_inverse/simple_inverse.hpp"

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <cblas.h>
#include <cmath>

#define SIZE 2000
#define MIN_VAL -10000
#define MAX_VAL 10000
#define ACCUR 10

void check_multy()
{
    mat_t A = get_random_matrix(SIZE, MIN_VAL, MAX_VAL);
    mat_t B = get_random_matrix(SIZE, MIN_VAL, MAX_VAL);

    for (int i = 0; i < 5; i++)
    {
        mat_t C = get_zero_matrix(SIZE);
        auto start = std::chrono::high_resolution_clock::now();
        mat_t tB = transpose_matrix(B, SIZE);
        mul_matrix(A, tB, C, SIZE);
        free_matrix(C);
        auto end = std::chrono::high_resolution_clock::now();
        free_matrix(tB);
        std::cout << "Custom mul_matrix time: "
                  << std::chrono::duration<double>(end - start).count() << " s\n";
    }

    float *C_blas = (float *)malloc(SIZE * SIZE * sizeof(float));

    auto bstart = std::chrono::high_resolution_clock::now();

    cblas_sgemm(
        CblasRowMajor,
        CblasNoTrans,
        CblasNoTrans,
        SIZE,
        SIZE,
        SIZE,
        1.0f,
        A,
        SIZE,
        B,
        SIZE,
        0.0f,
        C_blas,
        SIZE);

    auto bend = std::chrono::high_resolution_clock::now();

    std::cout << "BLAS multiplication time: "
              << std::chrono::duration<double>(bend - bstart).count() << " s\n";

    free_matrix(A);
    free_matrix(B);
    free(C_blas);
}

int check_inverse()
{
    mat_t A = get_random_matrix(SIZE, MIN_VAL, MAX_VAL);

    // Simple
    auto start = std::chrono::high_resolution_clock::now();
    float *inv_naive = simple_inverse(A, SIZE, ACCUR);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Naive multiplication inverse: "
              << std::chrono::duration<double>(end - start).count() << " s\n";
    free_matrix(inv_naive);

    // fast block matrix
    start = std::chrono::high_resolution_clock::now();
    float *inv_block = get_inverse_matrix(A, SIZE, ACCUR);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Block multiplication inverse: "
              << std::chrono::duration<double>(end - start).count() << " s\n";
    free_matrix(inv_block);

    // BLAS
    start = std::chrono::high_resolution_clock::now();
    float *inv_blas = inverse_by_series_blas(A, SIZE, ACCUR);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "BLAS multiplication inverse: "
              << std::chrono::duration<double>(end - start).count() << " s\n";
    free_matrix(inv_blas);

    free_matrix(A);
    return 0;
}

int main()
{
    srand(0);
    check_multy();
    check_inverse();
}
