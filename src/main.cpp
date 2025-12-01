#include <chrono>
#include <cstdlib>
#include <iostream>

#include "matrix_lib/matrix_lib.h"
#include "matrix_lib/utils/utils.h"

#include <cblas.h>

#define SIZE 1000
#define MIN_VAL -10000
#define MAX_VAL 10000

int main()
{
    srand(0);

    mat_t A = get_random_matrix(SIZE, MIN_VAL, MAX_VAL);
    mat_t B = get_random_matrix(SIZE, MIN_VAL, MAX_VAL);

    auto start = std::chrono::high_resolution_clock::now();
    mat_t tB = transpose_matrix(B, SIZE);
    mat_t C = mul_matrix(A, tB, SIZE);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Custom mul_matrix time: "
              << std::chrono::duration<double>(end - start).count() << " s\n";

    float *C_blas = (float *)malloc(SIZE * SIZE * sizeof(float));

    start = std::chrono::high_resolution_clock::now();

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

    end = std::chrono::high_resolution_clock::now();

    std::cout << "BLAS multiplication time: "
              << std::chrono::duration<double>(end - start).count() << " s\n";

    free(A);
    free(B);
    free(tB);
    free(C);
    free(C_blas);

    return 0;
}
