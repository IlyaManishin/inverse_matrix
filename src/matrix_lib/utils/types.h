#pragma once
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef const float *const_row_t;
    typedef const const_row_t* const_matrix_t;
    typedef float *row_t;
    typedef row_t* matrix_t;

#ifdef __cplusplus
}
#endif