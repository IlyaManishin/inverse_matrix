add_subdirectory(matrix_lib)

add_executable(main main.c)
target_link_libraries(main PRIVATE matrix_lib)