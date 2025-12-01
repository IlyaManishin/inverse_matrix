#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "matrix_lib/matrix_lib.h"
#include "matrix_lib/utils/utils.h"

#include <Eigen/Dense>

#define SIZE 1000

// Функция заполнения матрицы случайными числами
void fill_random(matrix_t mat, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            mat[i][j] = static_cast<float>(rand()) / RAND_MAX;
}

int main()
{
    srand(0);

    // Создаем и заполняем матрицы
    matrix_t A = get_zero_matrix(SIZE);
    matrix_t B = get_zero_matrix(SIZE);
    float *buf = (float *)malloc(SIZE * sizeof(float));

    fill_random(A, SIZE);
    fill_random(B, SIZE);

    // Таймер для вашей функции
    auto start = std::chrono::high_resolution_clock::now();
    matrix_t tB = transpose_matrix(B, SIZE);
    matrix_t C = mul_matrix((const_matrix_t)A, (const_matrix_t)tB, buf, SIZE);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Custom mul_matrix time: "
              << std::chrono::duration<double>(end - start).count() << " s\n";

    // Используем Eigen
    Eigen::MatrixXf EA(SIZE, SIZE);
    Eigen::MatrixXf EB(SIZE, SIZE);
    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
        {
            EA(i, j) = A[i][j];
            EB(i, j) = B[i][j];
        }

    start = std::chrono::high_resolution_clock::now();
    Eigen::MatrixXf EC = EA * EB;
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Eigen multiplication time: "
              << std::chrono::duration<double>(end - start).count() << " s\n";

    // Освобождение памяти
    free_matrix(A, SIZE);
    free_matrix(B, SIZE);
    free_matrix(tB, SIZE);

    free(buf);

    return 0;
}
