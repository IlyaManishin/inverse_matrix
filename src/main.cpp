#include <chrono>
#include <cstdlib>
#include <iostream>

#include "matrix_lib/matrix_lib.h"
#include "matrix_lib/utils/utils.h"

#include <Eigen/Dense>

#define SIZE 1000
#define MIN_VAL -10000
#define MAX_VAL 10000

int main()
{
    srand(0);

    // Создаем и заполняем матрицы
    mat_t A = get_random_matrix(SIZE, MIN_VAL, MAX_VAL);
    mat_t B = get_random_matrix(SIZE, MIN_VAL, MAX_VAL);

    // Таймер для вашей функции
    auto start = std::chrono::high_resolution_clock::now();
    mat_t tB = transpose_matrix(B, SIZE);
    mat_t C = mul_matrix(A, tB, SIZE);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Custom mul_matrix time: "
              << std::chrono::duration<double>(end - start).count() << " s\n";

    // Используем Eigen
    Eigen::MatrixXf EA(SIZE, SIZE);
    Eigen::MatrixXf EB(SIZE, SIZE);

    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
        {
            EA(i, j) = A[i * SIZE + j];
            EB(i, j) = B[i * SIZE + j];
        }

    start = std::chrono::high_resolution_clock::now();
    Eigen::MatrixXf EC = EA * EB;
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Eigen multiplication time: "
              << std::chrono::duration<double>(end - start).count() << " s\n";

    free(A);
    free(B);
    free(tB);
    free(C);

    return 0;
}
