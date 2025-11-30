cmake_minimum_required(VERSION 3.16)

project(inverse_matrix)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

add_subdirectory(src)
add_subdirectory(tests)