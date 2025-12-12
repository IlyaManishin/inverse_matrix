#pragma once

#include <cstdlib>
typedef float* mat_t;

mat_t inverse_by_series_blas(const mat_t A, size_t n, size_t accur);
