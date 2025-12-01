add_subdirectory(matrix_lib)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE matrix_lib)
target_link_libraries(main PRIVATE openblas)
