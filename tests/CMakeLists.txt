add_executable(tests tests.cpp)

target_link_libraries(tests PRIVATE matrix_lib GTest::gtest GTest::gtest_main)
target_link_libraries(tests PRIVATE openblas)

add_test(NAME matrix_lib_test COMMAND tests --gtest_color=yes)
gtest_discover_tests(tests)
