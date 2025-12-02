#pragma once

#include "utils/types.h"

#include <stdlib.h>
#ifdef __cplusplus
extern "C"
{
#endif

    mat_t get_zero_matrix(size_t size);
    mat_t get_identity_matrix(size_t size);
    mat_t get_random_matrix(size_t size, float min_val, float max_val);

    void free_matrix(mat_t matrix);
    float *get_inverse_matrix(mat_t matrix, size_t size, size_t accur);

#ifdef __cplusplus
}
#endif