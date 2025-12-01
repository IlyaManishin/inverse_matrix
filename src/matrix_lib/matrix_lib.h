#pragma once

#include "utils/types.h"

#include <stdlib.h>
#ifdef __cplusplus
extern "C"
{
#endif

    float **get_zero_matrix(size_t size);
    float **get_identity_matrix(size_t size);

    void free_matrix(float **matrix, size_t size);
    float **get_inverse_matrix(const float **matrix, size_t size);

#ifdef __cplusplus
}
#endif