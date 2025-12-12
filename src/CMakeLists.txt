add_subdirectory(matrix_lib)

add_executable(main
    main.cpp
    test_inverse/blas_inverse.cpp
    test_inverse/simple_inverse.cpp)

target_link_libraries(main PRIVATE matrix_lib)
target_link_libraries(main PRIVATE openblas)
target_link_libraries(main PRIVATE m)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(main PUBLIC OpenMP::OpenMP_CXX)
endif()

