#pragma once
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void free_matrix(float **matrix, size_t size);
    float **inverse_matrix(float **matrix, size_t size);

#ifdef __cplusplus
}
#endif