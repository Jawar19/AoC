add_executable(dec_1_test dec_1/test_main.cc)

target_link_libraries(dec_1_test dec_1_logic GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(dec_1_test)
