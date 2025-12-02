#include "matrix_lib/matrix_lib.h"
#include "matrix_lib/utils/utils.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <cstring>

#include <cblas.h>

#define SIZE 1000
#define MIN_VAL -10000
#define MAX_VAL 10000
#define ACCUR 20

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

// void check_inverse_speed() {
//     srand(0);

//     mat_t A = get_random_matrix(SIZE, MIN_VAL, MAX_VAL);

//     // Custom inverse
//     for (int i = 0; i < 5; i++) {
//         auto start = std::chrono::high_resolution_clock::now();
//         mat_t invA = get_inverse_matrix(A, SIZE, ACCUR);
//         auto end = std::chrono::high_resolution_clock::now();

//         std::cout << "Custom inverse time: "
//                   << std::chrono::duration<double>(end - start).count() << " s\n";

//         free_matrix(invA);
//     }

//     // BLAS method: solve A * X = I
//     mat_t I = get_identity_matrix(SIZE);
//     mat_t inv_blas = get_zero_matrix(SIZE);

//     for (int i = 0; i < 5; i++) {
//         memcpy(inv_blas, I, SIZE * SIZE * sizeof(float));

//         auto start = std::chrono::high_resolution_clock::now();

//         // Используем LU-разложение + обратную матрицу
//         int *ipiv = (int *)malloc(SIZE * sizeof(int));
//         int info;

//         sgetrf_(&SIZE, &SIZE, inv_blas, &SIZE, ipiv, &info); // LU
//         sgetri_(&SIZE, inv_blas, &SIZE, ipiv, nullptr, &SIZE * SIZE, &info); // inverse
        

//         auto end = std::chrono::high_resolution_clock::now();

//         std::cout << "BLAS inverse time: "
//                   << std::chrono::duration<double>(end - start).count() << " s\n";

//         free(ipiv);
//     }

//     free_matrix(A);
//     free_matrix(I);
//     free_matrix(inv_blas);
// }


int main()
{
    srand(0);
    check_multy();

}
