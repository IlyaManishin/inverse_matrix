add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE matrix_lib GTest::gtest GTest::gtest_main)
add_test(NAME matrix_lib_test COMMAND tests)
gtest_discover_tests(tests)
